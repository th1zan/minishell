/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:34:31 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	g_env = env;
	input_loop(env);
	free_global_env(g_env);
	return (0);
}

int	count_env_entries(char **envp)
{
	int	count;

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
	char	cwd[1024];

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
	int		*delimiter_tab;

	delimiter_tab = NULL;
	delimiter_tab = get_delimiter(input);
	if (!delimiter_tab)
	{
		env->error_parsing = 1;
		return (1);
	}
	input_to_token(input, &(g_env->tk_head), delimiter_tab);
	free(delimiter_tab);
	if (parse_token(&(g_env->tk_head)))
		return (-1);
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
			continue ;
		}
		if (is_blank_str(input))
		{
			free(input);
			continue ;
		}
		if (parse_input(input, env))
		{
			free(input);
			free_lst(env->tk_head);
			env->tk_head = NULL;
			continue ;
		}
		if (check_parsing(env->tk_head))
		{
			free(input);
			free_lst(env->tk_head);
			env->tk_head = NULL;
			continue ;
		}
		if (set_redirection(&(env->tk_head)))
		{
			free_lst(env->tk_head);
			env->tk_head = NULL;
			continue ;
		}
		execution(env, &(env->tk_head));
		restore_std(original_std);
		free(input);
		free_lst(env->tk_head);
		env->tk_head = NULL;
	}
	return (0);
}

char	*get_line(char *prompt)
{
	struct termios	saved;
	struct termios	attributes;
	char			*line;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	line = readline(prompt);
	if (line == NULL)
		return (NULL);
	create_history(line);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	return (line);
}

char	**get_path_tab(char **env_main)
{
	char	**path;
	int		i;
	char	*tmp;

	path = NULL;
	i = 0;
	while (env_main && env_main[i] != 0)
	{
		if (ft_strnstr(env_main[i], "PATH=", 5) != 0)
			break ;
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
	return (0);
}

int	restore_std(int *original_std)
{
	if (dup2(original_std[0], STDIN_FILENO) == -1)
	{
		perror("dup2 error: original_std[0] in restore_std");
		return (-1);
	}
	if (dup2(original_std[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 error: original_std[1] in restore_std");
		return (-1);
	}
	if (dup2(original_std[2], STDERR_FILENO) == -1)
	{
		perror("dup2 error: original_std[2] in restore_std");
		return (-1);
	}
	close(original_std[0]);
	close(original_std[1]);
	close(original_std[2]);
	return (0);
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
	g_env->status = 1;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	create_history(char *input)
{
	int	fd;

	add_history(input);
	fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
}
