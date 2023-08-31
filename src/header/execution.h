/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:15:49 by mlachat           #+#    #+#             */
/*   Updated: 2023/09/01 01:14:31 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

//pipex
// int		get_fd(char *file, int in_out);
// int		pipe_fd(int *fd_tab);
// int		fork_fct(int *pipe_tab, char **argv, char **path);
// int		exec_function(char *fct, char **path);
// char	**get_path(char **envp);
// int		iswhitespace(int c);
// int		check_empty(char **tab_str, int from, int to);
// int		free_tab(char **tab);
// int		check_access(char *fct, char **fct_arg);
// int		exec_err(char *error_msg, char **fct_arg);
// int		empty_fct_err(int cmd);

//exec
int		execution(t_tk **tk);
char	*arg_to_str(t_tk *tk);
// void    bin_execution(t_env *env, t_cmd *cmd);
// void	execution(t_env *env);
// int	    execute_cmd(t_env *env, t_token *token);
// int	    wait_all_pid(t_env *env);

//join
// int		check_parsing(t_tk *tk);

#endif