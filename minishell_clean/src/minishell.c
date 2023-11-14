/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/11/14 11:30:18 by thibault         ###   ########.fr       */
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

int	execute_command(t_env *env, char *input)
{
	if (set_redirection(&(env->tk_head)))
	{
		free_lst(env->tk_head);
		env->tk_head = NULL;
		return (1);
	}
	execution(env, &(env->tk_head));
	free(input);
	free_lst(env->tk_head);
	env->tk_head = NULL;
	return (0);
}

int	process_main_input(t_env *env, char *input)
{
	if (is_blank_str(input) || parse_input(input, env)
		|| check_parsing(env->tk_head))
	{
		free(input);
		free_lst(env->tk_head);
		env->tk_head = NULL;
		return (1);
	}
	// print_lst(g_env->tk_head);
	return (execute_command(env, input));
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
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (*input == 0)
		{
			free(input);
			continue ;
		}
		if (!process_main_input(env, input))
			restore_std(original_std);
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
