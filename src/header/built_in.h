#ifndef BUILT_IN_H
# define BUILT_IN_H

/*built_in.c*/
int	echo(t_tk *tk);
// int	echo(t_tk *cmd, int backslash_n, int i);
int	cd(t_tk *cmd);
int	pwd(t_tk *cmd);
int	export(t_tk *cmd);
int	unset(t_tk *cmd, t_tk );
int	env(t_tk *cmd);
int	exit_cmd(t_tk *cmd);

/*built_in.c*/
int	is_builtin_exec(t_tk *cmd);
int	is_echo(t_tk *tk);
int	is_tk_str(t_tk *tk, char *fct_name);

#endif