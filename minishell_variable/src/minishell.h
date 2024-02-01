/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:13:42 by thibault          #+#    #+#             */
/*   Updated: 2024/02/01 14:09:17 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*System's headers*/
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>

/*Minishell header files*/
# include "./header/struct.h"
# include "./header/enum_token.h"
# include "./libft/libft.h"
# include "./header/check_fct.h"
# include "./header/parsing.h"
# include "./header/built_in.h"
# include "./header/utils.h"
# include "./header/redirection.h"
# include "./header/execution.h"

extern int	g_status;

/* minishell.c */
int		main(int argc, char **argv, char **envp);
int		execute_command(t_env *env, char *input);
int		process_main_input(t_env *env, char *input);
int		input_loop(t_env *env);
char	*get_line(char *prompt);

/* init_env.c */
int		count_env_entries(char **envp);
char	**copy_env(char **envp, int count);
t_env	*init_env(char **envp);
int		parse_input(char *input, t_env *env);
char	**get_path_tab(char **env_main);

/* signal.c */
int		save_std(int *original_std);
int		restore_std(int *original_std);
void	handle_signal(t_env *env);
void	handle_sigint(int signo);
void	create_history(char *input);
#endif