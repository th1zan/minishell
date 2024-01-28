/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:44:47 by thibault          #+#    #+#             */
/*   Updated: 2024/01/27 15:29:15 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

/*built_in_cd.c*/
int		add_new_oldpwd(char *current_directory, t_env *env);
int		update_oldpwd(char *current_directory, t_env *env);
int		cd(t_tk *tk);

/*built_in_echo.c*/
void	print_args(t_tk *tk, t_tk *tmp, int newline);
int		echo(t_tk *tk);

/*built_in_env_pwd.c*/
int		env_built_in(t_tk *tk);
int		pwd(t_tk *tk);

/*built_in_exit.c*/
int		exit_status_error(char *arg);
int		exit_builtin(t_tk *cmd);
int		is_str_with_alpha(char *str);
int		is_all_digit(char *str);

/*built_in_export_1.c*/
int		export(t_tk *tk);
int		handle_new_var(t_env *env, char *new_var);
int		update_or_add_env_var(t_env *env, char *new_var);
int		add_new_env_var(t_env *env_struct, char **env, char *new_var);
void	update_path_tab(t_env *env);

/*built_in_export_2.c*/
char	*concat_args(t_tk *tk);
t_tk	*advance_and_free(t_tk *tk);
int		find_env_var(char **env, char *var_name);
int		is_valid_env_argument(char *arg);
int		validate_env_arg_characters(char *arg);

/*built_in_unset.c*/
void	remove_env(t_env *env_struct, int index);
void	check_path_var(t_env *env, char *var);
int		unset(t_tk *tk);

/*is_built_in_1.c*/
int		is_tk_str(t_tk *tk, char *fct_name);
int		is_echo(t_tk *tk);
int		is_export(t_tk *tk);
int		is_unset(t_tk *tk);
int		is_env(t_tk *tk);

/*is_built_in_2.c*/
int		is_pwd(t_tk *tk);
int		is_cd(t_tk *tk);
int		is_exit(t_tk *tk);
int		is_builtin_exec(t_tk *cmd);
int		is_builtin_cmd_tk(t_tk *cmd);
#endif