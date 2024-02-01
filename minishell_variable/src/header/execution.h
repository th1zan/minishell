/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:15:49 by mlachat           #+#    #+#             */
/*   Updated: 2024/01/31 11:10:35 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*execution.c*/
void	free_resources(char **cmd, char ***arg_table);
int		handle_fork_error(char **cmd, char ***arg_table);
void	exe_child_process(t_env *env, t_tk *tmp, char **cmd, char ***arg_table);
int		execute_non_builtin(t_env *env, t_tk *tmp);
int		execution(t_env *env, t_tk **tk);

/*handle_cmd.c*/
int		cmd_arg_list_to_table(t_tk *tk, char ***arg_table, char **cmd);
int		tk_arg_to_table(t_tk *tk, char	***arg_table);
int		check_and_set_path(t_tk *tk, char *cmd, char *path);
int		get_cmd_path(t_tk *tk);

/*status.c*/
void	free_and_replace(char **env, char *new_var, int index);
char	**create_new_env(char **env, char *new_var, int size);
t_tk	*get_prev_cmd_tk(t_tk *tk);
int		update_status_variable(t_env *env, int bin_status, int status_built_in);

/*wait_and_close.c*/
int		fd_is_standard(int fd);
int		close_all_fd(t_tk **tk);
int		wait_all_pid(t_tk **tk);
int		get_status_info(int status);

#endif