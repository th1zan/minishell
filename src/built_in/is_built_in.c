/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:24:48 by thibault          #+#    #+#             */
/*   Updated: 2023/10/09 17:13:14 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_tk_str(t_tk *tk, char *fct_name)
{
	char	*cmd_str;
	int		len;

	cmd_str = tk->tk_str;
	len = ft_strlen(fct_name);
	if(ft_strncmp(cmd_str, fct_name, len) == 0)
		return(1);
	return (0);
}

int	is_echo(t_tk *tk)
{
	return(is_tk_str(tk, "echo"));
}

int	is_export(t_tk *tk)
{
	return(is_tk_str(tk, "export"));
}

int	is_unset(t_tk *tk)
{
	return(is_tk_str(tk, "unset"));
}

int	is_env(t_tk *tk)
{
	return(is_tk_str(tk, "env"));
}

int	is_pwd(t_tk *tk)
{
	return(is_tk_str(tk, "pwd"));
}

int	is_cd(t_tk *tk)
{
	return(is_tk_str(tk, "cd"));
}
int	is_exit(t_tk *tk)
{
	return(is_tk_str(tk, "exit"));
}


int	is_builtin_exec(t_tk *cmd)
{
	int	status;

	status = -1;
	if (is_echo(cmd))
		status = echo(cmd);
	else if (is_cd(cmd))
		status = cd(cmd);
    else if (is_pwd(cmd))
		status = pwd();
	else if (is_export(cmd))
		status = export(cmd);
	else if (is_unset(cmd))
		status = unset(cmd);
	else if (is_env(cmd))
		status = env_built_in(cmd);
	else if (is_exit(cmd))
	{
		status = 0;
		printf("exit\n");
		if (cmd->tk_arg)
			printf("minishell: exit: exit does not take any arguments\n");
		
		//free all variable before exit
		exit(status);
	}
	// fprintf(stderr, "===INFO===: in :: is_builtin_exec: status = %d\n", status);
	return (status);
}

int	is_builtin_cmd_tk(t_tk *cmd)
{
	int	status;

	status = -1;
	if (is_echo(cmd))
		status = 1;
	else if (is_cd(cmd))
		status = 1;
    else if (is_pwd(cmd))
		status = 1;
	else if (is_export(cmd))
		status = 1;
	else if (is_unset(cmd))
		status = 1;
	else if (is_env(cmd))
		status = 1;
	else if (is_exit(cmd))
		status = 1;
	return (status);
}