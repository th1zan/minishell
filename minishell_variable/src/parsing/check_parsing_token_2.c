/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_token_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:45:21 by thibault          #+#    #+#             */
/*   Updated: 2024/02/01 14:58:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	try_paths(t_env *env, char **path_tab, char *cmd)
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
		if (check_access(env, full_cmd) == SUCCESS)
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
	t_env	*env;

	cmd = tk->tk_str;
	env = tk->env_struct;
	if (cmd[0] == '/' && check_access(env, cmd) == SUCCESS)
		return (SUCCESS);
	if (!tk->env_struct->path_tab)
	{
		tk->env_struct->status = 127;
		cmd_err(tk->env_struct->status, cmd);
		return (FAILURE);
	}
	if (try_paths(env, tk->env_struct->path_tab, cmd) == SUCCESS)
		return (SUCCESS);
	cmd_err(tk->env_struct->status, cmd);
	return (FAILURE);
}

int	check_access(t_env *env, char *cmd)
{
	(void)env;
	if (access(cmd, F_OK) == -1)
	{
		env->status = 127;
		g_status = 127;
		return (FAILURE);
	}
	else if (access(cmd, X_OK) == -1)
	{
		g_status = 126;
		return (FAILURE);
	}
	g_status = 0;
	return (SUCCESS);
}
