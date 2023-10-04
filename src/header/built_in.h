#ifndef BUILT_IN_H
# define BUILT_IN_H

/*built_in.c*/

// int	echo(t_tk *cmd, int backslash_n, int i);
// int	cd(t_tk *cmd);
// int	pwd(t_tk *cmd);
// int	export(t_tk *cmd);
// int	unset(t_tk *cmd, t_tk );
// int	env(t_tk *cmd);
// int	exit_cmd(t_tk *cmd);

/*built_in.c*/
int		echo(t_tk *tk);
int		unset(t_tk *tk);
int		export(t_tk *tk);
int		env_built_in(t_tk *tk);
int		find_env_var(char **env, char *var_name);
int		is_valid_env_argument(char *arg);


int		is_tk_str(t_tk *tk, char *fct_name);
int		is_echo(t_tk *tk);

char	*concat_args(t_tk *tk);
void	add_or_update_env(char **env, char *new_var);
int		is_export(t_tk *tk);
int		is_valid_env_argument(char *arg);

/*is_built_in.c*/
int		is_unset(t_tk *tk);
int		is_env(t_tk *tk);
int		is_builtin_exec(t_tk *cmd);
int		is_builtin(t_tk *cmd);



#endif