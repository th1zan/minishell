/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:13:42 by thibault          #+#    #+#             */
/*   Updated: 2023/10/12 16:44:54 by thibault         ###   ########.fr       */
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
# include "./header/envir.h"
# include "./header/check_fct.h"
# include "./header/parsing.h"
# include "./header/built_in.h"
# include "./header/utils.h"
# include "./header/execution.h"

extern t_env	*global_env;

/* Minishell.c */
t_env	*init_env(char **envp);
int		parse_input(char *input, t_env *env);
int		input_loop(t_env *env);
char	*get_line(char *prompt);
char	**get_path_tab(char **envp);
int		save_std(int *original_std);
int		restore_std(int *original_std);
void	handle_signal(void) ;
void	handle_sigint(int signo);
void	create_history(char *input);





#endif