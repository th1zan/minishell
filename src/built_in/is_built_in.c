/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:24:48 by thibault          #+#    #+#             */
/*   Updated: 2023/09/25 10:56:09 by thibault         ###   ########.fr       */
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
	printf("is_echo status: %d\n", is_tk_str(tk, "echo"));
	return(is_tk_str(tk, "echo"));
}


int	is_builtin_exec(t_tk *cmd)
{
	int	status;

	status = -1;
	if (is_echo(cmd))
		status = echo(cmd);
	// else if (is_cd(cmd))
	// 	status = cd(cmd);
    // else if (is_pwd(cmd))
	// 	status = pwd(cmd);
	// else if (is_export(cmd))
	// 	status = export(cmd);
	// else if (is_unset(cmd))
	// 	status = unset(cmd);
	// else if (is_env(cmd))
	// 	status = env(cmd);
	// else if (is_exit(cmd))
	// {
	// 	status = 0;
	// 	exit(cmd);
	// }
	return (status);
}