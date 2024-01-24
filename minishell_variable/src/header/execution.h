/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:15:49 by mlachat           #+#    #+#             */
/*   Updated: 2023/11/03 14:17:34 by thibault         ###   ########.fr       */
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
int		save_status_var_in_env(t_env *env_tk);
int		update_status_variable(t_env *env, int bin_status, int status_built_in);

/*wait_and_close.c*/
int		fd_is_standard(int fd);
int		close_all_fd(t_tk **tk);
int		wait_all_pid(t_tk **tk);
int		get_status_info(int status);

#endif