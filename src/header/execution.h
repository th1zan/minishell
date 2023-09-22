/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:15:49 by mlachat           #+#    #+#             */
/*   Updated: 2023/09/21 18:36:23 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*redirection.c*/
int		set_redirection(t_tk **tk);
int		set_default_fd(t_tk **tk);
int		set_pipe_fd(t_tk **tk);
int		set_operator_fd(t_tk **tk);
int		open_file_to_fd(char *file, int option);
int		redir_operator_fd(t_tk **tk);
int		set_fd_for_cmd(t_tk *tk);


int		set_cmd_pipe_fd(t_tk **tk);
int		set_cmd_operator_fd(t_tk **tk);
int		set_cmd_std_fd(t_tk **tk);
int		close_tk_fd(t_tk *tk);
int		close_all_fd(t_tk **tk);
t_tk	*get_prev_type_tk(t_tk *tmp, int type);
t_tk	*get_next_type_tk(t_tk *tmp, int type);


/*execution.c*/
int		execution(t_tk **tk);
int		tk_arg_to_table(t_tk *tk, char	***arg_table);
int		wait_all_pid(t_tk **tk);
int		get_cmd_path(t_tk *tk);
char	*arg_to_str(t_tk *tk);
int		cmd_fd_is_standard(t_tk *cmd);
int		fd_is_standard(int fd);

//pipex
// int		get_fd(char *file, int in_out);
// int		pipe_fd(int *fd_tab);
// int		fork_fct(int *pipe_tab, char **argv, char **path);
// int		exec_function(char *fct, char **path);
// char		**get_path(char **envp);
// int		iswhitespace(int c);
// int		check_empty(char **tab_str, int from, int to);
// int		free_tab(char **tab);
// int		check_access(char *fct, char **fct_arg);
// int		exec_err(char *error_msg, char **fct_arg);
// int		empty_fct_err(int cmd);



// void    bin_execution(t_env *env, t_cmd *cmd);
// void	execution(t_env *env);
// int	    execute_cmd(t_env *env, t_token *token);
// int	    wait_all_pid(t_env *env);

//join
// int		check_parsing(t_tk *tk);

#endif