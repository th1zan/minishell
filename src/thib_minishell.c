/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/10/10 22:47:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*global_env;

int	main(int argc, char **argv, char **envp)
{
	
	(void)argc;
	(void)argv;
	t_env	*env;
	
	env = init_env(envp);
	global_env = env;
	input_loop(env);

	// free_env(env);
	return(0);
	
}


t_env	*init_env(char **envp)
{
	t_env *new_env;

	if (envp == NULL || *envp == NULL)
	{
		printf("minishell: environment is NULL.\n");
	}
	
	new_env = (t_env *)calloc(1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->env_main = envp;
	new_env->status = 0;
	return (new_env);
}

int	parse_input(char *input, t_env *env)
{
	// t_tk	*tk_head;
	int		*delimiter_tab;
	// char	**env_main;

	// tk_head = env->tk_head;
	// env_main = env->env_main;

	delimiter_tab = NULL;
	delimiter_tab = get_delimiter(input);  // This array of ints the size of the input, will be used to mark whether each character in the input is a delimiter (1) or not (0).

	if(!delimiter_tab)
	{
		env->error_parsing = 1;
		return(1);
	}
	
	
	input_to_token(input, &(env->env_main), &(env->tk_head), delimiter_tab);
	// here we have a linked list, with each node is a part of the input seperated with the delimiter, that was set in the delimiter array of int.
	
	// if ft_calloc called in get_delimiter, return NULL (shit happens), you can't free it, you'll have a memory problem. 
	free(delimiter_tab);
	parse_token(&(env->tk_head));

		//DEBUG
		fprintf(stderr, "===INFO===: end of parsing\n");
		// fprintf(stderr, "===INFO===: print PATH\n");
		// print_strtab(tk_head->path_tab);
		// fprintf(stderr, "===INFO===: print ENV\n");
		// print_strtab(tk_head->env);
	return (0);
}

int	input_loop(t_env *env)
{
	char	*input;
	int	original_std[3];
	
	while (1)
	{
		save_std(original_std);
		handle_signal();
		input = get_line("minishell> ");
		if (!input) // == gestion de ctrl-D aka EOF
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input == 0)
		{	
			free(input);
			continue;
		}
		if (is_blank_str(input))
		{
			free(input);
			continue;
		}
		if (parse_input(input, env))
		{	
			free(input);
			continue;
		}
		
		//DEBUG
		fprintf(stderr, "===INFO===: print parsed input -> TK list::\n");
		print_lst(env->tk_head);
		if (check_parsing(env->tk_head))
		{
			// DEBUG
			printf("minishell: %d : parsing error\n", global_env->error_parsing);
			
			free(input);
			continue;
		}
		
		set_redirection(&(env->tk_head));
		
		//DEBUG
		// fprintf(stderr, "===INFO===: print TK list before execution::\n");
		// print_lst(tk_head);
		fprintf(stderr, "===INFO===: result of cmd line (if displayed)::\n");
		
		execution(env, &(env->tk_head));
		restore_std(original_std);

		//DEBUG
		fprintf(stderr, "===INFO===: initial input:: %s\n", input);
		free(input);
		// fprintf(stderr, "===INFO===: $?:: %d\n", env->status);
	}
	
	return(0);
}


void free_tk(t_tk *tk)
{
	if (!tk)
		return;

	free_tk(tk->next); // Récursion pour libérer la liste liée

	if (tk->tk_str)
		free(tk->tk_str);
	if (tk->env && *tk->env)
		free(*tk->env); // Si vous avez alloué chaque ligne de env séparément, vous devrez peut-être ajouter une boucle ici pour les libérer toutes.
	if (tk->path_tab)
	{
		char **path = tk->path_tab;
		while (*path)
		{
			free(*path);
			path++;
		}
		free(tk->path_tab);
	}
	if (tk->path)
		free(tk->path);
	if (tk->tk_arg)
		free(tk->tk_arg); // Assurez-vous que tk_arg est bien une structure allouée dynamiquement et non une référence à une autre structure déjà libérée.

	free(tk);
}

void free_env(t_env *env)
{
	char **env_line;
	
	if (!env)
		return;

	if (env->tk_head)
		free_tk(env->tk_head);

	if (env->env_main)
	{
		env_line = env->env_main;
		while (*env_line)
		{
			free(*env_line);
			env_line++;
		}
		free(env->env_main);
	}

	free(env);
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
	if (!env_main[i])
	{
		return (path);
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