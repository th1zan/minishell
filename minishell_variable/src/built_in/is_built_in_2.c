/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:38:33 by thibault          #+#    #+#             */
/*   Updated: 2024/01/29 15:06:45 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pwd(t_tk *tk)
{
	return (is_tk_str(tk, "pwd"));
}

int	is_cd(t_tk *tk)
{
	return (is_tk_str(tk, "cd"));
}

int	is_exit(t_tk *tk)
{
	return (is_tk_str(tk, "exit"));
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
		status = pwd(cmd);
	else if (is_export(cmd))
		status = export(cmd);
	else if (is_unset(cmd))
		status = unset(cmd);
	else if (is_env(cmd))
		status = env_built_in(cmd);
	else if (is_exit(cmd))
	{
		status = exit_builtin(cmd);
		free_env(cmd->env_struct);
		exit(status);
	}
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
