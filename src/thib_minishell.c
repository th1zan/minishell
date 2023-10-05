/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/10/05 16:58:07 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pour les leaks, checkez "Instruments" a l'ecole il est sur les macs. Ca permet de lancer la commande leaks pendant que minishell tourne pour checker les leaks beaucoup plus facilement. Je vous montre si vous voulez.

#include "minishell.h"

// < IN_file grep a | wc -l > OUT_file

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tk	*tk_head;
	int		*delimiter_tab;
	char	**env_main;
	
	int	original_std[3];
	(void)argc;
	(void)argv;

	tk_head = NULL;
	delimiter_tab = NULL;
	env_main = envp;
	

	//envp can be sent empty into the program, check if empty before continuing to avoid wrong dereference (segfault)
	// tip : there is a bash command that you can run your program with in order to empty the envp that it receives. 
	// tip : when you run bash with this command, bash still add default env variables in the empty env. So you can do the same here, 
	
	// when receiving and empty env, to avoid segfault, add what you judge necessary and logic according to bash
	// printf("path adress:%p\n", path);
	// print_strtab(path);
	while (1)
	{
		// printf("main :: env_main: %p\n" ,env_main);
		save_std(original_std);
		handle_signal();
		input = get_line("minishell> ");

		if (!input) // == gestion de ctrl-D aka EOF
		{
			ft_printf("exit\n");
			break ;
		}

		if (check_input(input)) // return 1 means something is wrong. 
		{
			if (input != NULL)
				free(input);
			continue; // skip the current iteration, and starts a new one, in this case, goes back to reading the input with readline()
		}

		// replace_env_variables(&input);
		// fprintf(stderr, "===INFO===: New input with variable's content\n");
		// printf("%s\n", input);

		delimiter_tab = get_delimiter(input);  // This array of ints the size of the input, will be used to mark whether each character in the input is a delimiter (1) or not (0).

		// if delimiter_tab is NULL, sending it in input_to_token might not be safe.
		input_to_token(input, &env_main, &tk_head, delimiter_tab);
		// here we have a linked list, with each node is a part of the input seperated with the delimiter, that was set in the delimiter array of int.
		
		// if ft_calloc called in get_delimiter, return NULL (shit happens), you can't free it, you'll have a memory problem. 
		free(delimiter_tab);
		parse_token(&tk_head);
		fprintf(stderr, "===INFO===: end of parsing\n");
		
		// fprintf(stderr, "===INFO===: print PATH\n");
		// print_strtab(tk_head->path_tab);
		// fprintf(stderr, "===INFO===: print ENV\n");
		// print_strtab(tk_head->env);

		fprintf(stderr, "===INFO===: print TK list::\n");
		// if (check_parsing(tk_head) == 0)
		{
			fprintf(stderr, "===INFO===: end of parsing check\n");
			set_redirection(&tk_head);
			fprintf(stderr, "===INFO===: end of redirection\n");
			// fprintf(stderr, "===INFO===: print TK list::\n");
			// print_lst(tk_head);
			fprintf(stderr, "===INFO===: result of cmd line (if displayed)::\n");
			execution(&tk_head);
			fprintf(stderr, "===INFO===: end of execution\n");
			// print_lst(tk_head);
			restore_std(original_std);
		}
		fprintf(stderr, "===INFO===: initial input:: %s\n", input);
		free(input);
		
	}
	return(0);
}

char	*get_line(char *prompt)
{
	struct termios	saved;         // Structure pour sauvegarder les attributs actuels du terminal.
	struct termios	attributes;    // Structure pour définir de nouveaux attributs pour le terminal.
	char			*line;

	tcgetattr(STDIN_FILENO, &saved);  // Obtenir et sauvegarder les attributs actuels du terminal.
	tcgetattr(STDIN_FILENO, &attributes);  // Obtenir les attributs actuels du terminal pour les modifier.

	attributes.c_lflag &= ~ECHOCTL;  // Modifier les attributs pour désactiver l'affichage des caractères de contrôle. Ex: le caractère de contrôle Ctrl-C ne sera pas affiché comme "^C"
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);  // Définir les nouveaux attributs pour le terminal.

	line = readline(prompt);  // Lire une ligne de l'utilisateur en utilisant le prompt fourni.
	if (line == NULL) // Vérifier l'entrée de l'utilisateur (la fonction check_input n'est pas fournie, donc je ne peux pas dire exactement ce qu'elle fait).
		return (NULL);

	create_history(line);  // (Commenté) Ajouter la ligne à l'historique.

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);  // Restaurer les attributs originaux du terminal.

	return (line);  // Renvoyer la ligne lue.
}

char	**get_path(char **env_main)
{
	char	**path;
	int		i;
	char	*tmp;

	path = NULL;
	i = 0;
	
	// run minishell with NULL envp, might have a segfault here with the dereferencement.
	// proposition : while (envp && envp[i] != 0)
	
	while (env_main && env_main[i] != 0)
	{
		if (ft_strnstr(env_main[i], "PATH=", 5) != 0)
			break;
		i++;
	}
	path = ft_split(env_main[i], ':');
	if (path[0])
	{
		tmp = ft_strtrim(path[0], "PATH=");
		free (path[0]);
		path[0] = tmp;
	}
	// printf("IN SPLIT: path adress:%p\n", path);
	return (path);
}


int	check_input(char *input)
{
	if (input == NULL)
		return(1);
	if (*input == 0)
		return (1);
	return (0);
}

int	save_std(int *original_std)
{
	original_std[0] = dup(STDIN_FILENO);
	original_std[1] = dup(STDOUT_FILENO);
	original_std[2] = dup(STDERR_FILENO);
	if (original_std[0] == -1 || original_std[1] == -1 || original_std[2] == -1)
	{
		perror("dup error: original_std[0] in save_std");
		fprintf(stderr, "errno: %d\n", errno);
		return (-1);
	}
	return 0;
}

int	restore_std(int *original_std)
{
	if (dup2(original_std[0], STDIN_FILENO) == -1)
	{
		perror("dup2 error: original_std[0] in restore_std");
		fprintf(stderr, "original_std[0]: %d, errno: %d\n", original_std[0], errno);
		return (-1);
	}	
	if (dup2(original_std[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 error: original_std[1] in restore_std");
		fprintf(stderr, "original_std[1]: %d, errno: %d\n", original_std[1], errno);
		return (-1);
	}	
	if (dup2(original_std[2], STDERR_FILENO) == -1)
	{
		perror("dup2 error: original_std[2] in restore_std");
		fprintf(stderr, "original_std[2]: %d, errno: %d\n", original_std[2], errno);
		return (-1);
	}
	close(original_std[0]);
	close(original_std[1]);
	close(original_std[2]);
	return 0;
}


void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN); // Ctrl + backslash
	signal(SIGINT, handle_sigint); //Ctrl + C
	
}

void	handle_sigint(int signo) 
{
	(void)signo;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
	// update_variable_status_process(g_env, 130);
}

void	create_history(char *input)
{
	int	fd;

	add_history(input);
	fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
}