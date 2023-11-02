/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/11/01 18:23:37 by thibault         ###   ########.fr       */
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
	// print_strtab(global_env->env_main);
	input_loop(env);

	// free_env(env);
	free_global_env(global_env);
	return(0);
	
}

static int	count_env_entries(char **envp)
{
	int count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static char	**copy_env(char **envp, int count)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		new_env[i] = strdup(envp[i]);
		// printf("new_env[%d]: %s\n", i, new_env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
	}
	new_env[count] = NULL;
	return (new_env);
}

t_env	*init_env(char **envp)
{
	t_env	*new_env;
	int		count;
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	if (envp == NULL || *envp == NULL)
	{
		printf("minishell: environment is NULL.\n");
		return (NULL);
	}
	count = count_env_entries(envp);
	new_env = (t_env *)calloc(1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->env_main = copy_env(envp, count);
	// printf("new_env->env_main[2]: %s\n", new_env->env_main[2]);
	// print_strtab(new_env->env_main);
	
	if (!new_env->env_main)
	
	{
		free(new_env);
		return (NULL);
	}
	
	new_env->path_tab = get_path_tab(new_env->env_main);
	new_env->minishell_directory = ft_strdup(cwd);
	new_env->status = 0;
	new_env->tk_head = NULL;
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
	
	
	input_to_token(input, &(global_env->env_main), &(global_env->tk_head), delimiter_tab);
	// here we have a linked list, with each node is a part of the input seperated with the delimiter, that was set in the delimiter array of int.
	
	// if ft_calloc called in get_delimiter, return NULL (shit happens), you can't free it, you'll have a memory problem. 
	free(delimiter_tab);
	if (parse_token(&(global_env->tk_head)))
		return (-1);
	
		//DEBUG
		// fprintf(stderr, "===INFO===: end of parsing\n");
		// fprintf(stderr, "===INFO===: print PATH\n");
		// print_strtab(tk_head->path_tab);
		// fprintf(stderr, "===INFO===: print ENV\n");
		// print_strtab(tk_head->env);
	return (0);
}

int	input_loop(t_env *env)
{
	char	*input;
	int		original_std[3];
	
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
			free_lst(env->tk_head);
			// free(env->tk_head);
			env->tk_head = NULL;
			continue;
		}
		//DEBUG
		// fprintf(stderr, "===INFO===: print parsed input -> TK list::\n");
		// print_lst(env->tk_head);

		// printf("LOOP\n");
		// print_strtab(global_env->path_tab);
		if (check_parsing(env->tk_head))
		{
			// DEBUG
			// printf("minishell: %d : parsing grammar error\n", global_env->error_parsing);
			// printf("coucou1\n");
			free(input);
			// printf("coucou2\n");
			free_lst(env->tk_head);
			// free(env->tk_head);
			env->tk_head = NULL;
			// printf("coucou3\n");
			continue;
		}
		
		//DEBUG
		// fprintf(stderr, "===INFO===: print TK list before redirection::\n");
		// print_lst(env->tk_head);

		if (set_redirection(&(env->tk_head)))
		{
				// DEBUG
			// printf("coucou1\n");
			free(input);
			// printf("coucou2\n");
			free_lst(env->tk_head);
			// free(env->tk_head);
			env->tk_head = NULL;
			// printf("coucou3\n");
			continue;
		}
		
		// //DEBUG
		// fprintf(stderr, "===INFO===: print TK list before execution::\n");
		// print_lst(env->tk_head);
		// fprintf(stderr, "===INFO===: result of cmd line (if displayed)::\n");
		
		execution(env, &(env->tk_head));
		restore_std(original_std);

		//DEBUG
		// fprintf(stderr, "===INFO===: print TK list before freeing::\n");
		// print_lst(env->tk_head);
		// fprintf(stderr, "===INFO===: initial input:: %s\n", input);
		free(input);
		free_lst(env->tk_head);
		// free(env->tk_head);
		env->tk_head = NULL;
		
		// fprintf(stderr, "===INFO===: all variables freed::\n");
		
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

	// printf("line: %s %p\n", line, line);
	return (line);  // Renvoyer la ligne lue.
}

char	**get_path_tab(char **env_main)
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
	// printf("IN get_path: path adress:%p\n", path);
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
	global_env->status = 1;
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