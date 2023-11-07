/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_token_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:45:21 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:11:35 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	try_paths(char **path_tab, char *cmd)
{
	char	*temp;
	char	*full_cmd;
	int		i;

	i = 0;
	while (path_tab[i])
	{
		temp = ft_strjoin(path_tab[i], "/");
		full_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (check_access(full_cmd) == SUCCESS)
		{
			free(full_cmd);
			return (SUCCESS);
		}
		free(full_cmd);
		i++;
	}
	return (FAILURE);
}

int	test_cmd(t_tk *tk)
{
	char	*cmd;

	cmd = tk->tk_str;
	if (cmd[0] == '/' && check_access(cmd) == SUCCESS)
		return (SUCCESS);
	if (!g_env->path_tab)
	{
		g_env->status = 127;
		cmd_err(g_env->status, cmd);
		return (FAILURE);
	}
	if (try_paths(g_env->path_tab, cmd) == SUCCESS)
		return (SUCCESS);
	cmd_err(g_env->status, cmd);
	return (FAILURE);
}

int	check_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		g_env->status = 127;
		return (FAILURE);
	}
	else if (access(cmd, X_OK) == -1)
	{
		g_env->status = 126;
		return (FAILURE);
	}
	return (SUCCESS);
}
