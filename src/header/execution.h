/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:15:49 by mlachat           #+#    #+#             */
/*   Updated: 2023/10/18 15:57:55 by thibault         ###   ########.fr       */
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
int		set_cmd_std_fd(t_tk **tk);
int		set_cmd_pipe_fd(t_tk **tk);
int		set_cmd_operator_fd(t_tk **tk);
t_tk	*get_next_input_operator_tk(t_tk *tk);
t_tk	*get_prev_input_operator_tk(t_tk *tk);
t_tk	*get_next_output_operator_tk(t_tk *tk);
t_tk	*get_prev_output_operator_tk(t_tk *tk);

// TO DELETE
// int		close_tk_fd(t_tk *tk);
// t_tk	*get_prev_type_tk(t_tk *tmp, int type);


/*exec.c*/
int		execution(t_env *env, t_tk **tk);
t_tk	*get_next_cmd(t_tk *tmp);
t_tk	*get_next_type_tk(t_tk *tmp, int type);
t_tk	*get_prev_type_tk(t_tk *tk, int type);
int		cmd_arg_list_to_table(t_tk *tk, char ***arg_table, char **cmd);
int		tk_arg_to_table(t_tk *tk, char	***arg_table);
int		get_cmd_path(t_tk *tk);
int		set_fd_for_cmd(t_tk *tk);
int		fd_is_standard(int fd);
int		close_all_fd(t_tk **tk);
int		wait_all_pid(t_tk **tk);
int		get_status_info(int status);
int		save_status_var_in_env(t_env *env_tk);
int		update_status_variable(t_env *env, int bin_status, int ret_built_in);



// TO DELETE
// char	*arg_to_str(t_tk *tk);
// int	cmd_fd_is_standard(t_tk *cmd);



#endif