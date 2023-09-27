/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:13:42 by thibault          #+#    #+#             */
/*   Updated: 2023/09/27 17:04:42 by thibault         ###   ########.fr       */
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
# include <termios.h>


/*Minishell header files*/
# include "./header/struct.h"
# include "./header/enum_token.h"
# include "./libft/libft.h"
# include "./header/check_fct.h"
# include "./header/parsing.h"
# include "./header/built_in.h"
# include "./header/utils.h"
# include "./header/execution.h"

/* Minishell.c */
char	*get_line(char *prompt);
int		check_input(char *input);
char	**get_path(char **envp);
int		save_std(int *original_std);
int		restore_std(int *original_std);


#endif