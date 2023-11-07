/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:44:52 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 09:52:56 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(char **env, int index)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != index)
			new_env[j++] = env[i];
		else
			free(env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(env);
	g_env->env_main = new_env;
}

void	check_path_var(char *var)
{
	if (!ft_strncmp(var, "PATH", 4))
	{
		free(g_env->path_tab);
		g_env->path_tab = get_path_tab(g_env->env_main);
	}
}

int	unset(t_tk *tk)
{
	char	*target_var;
	int		index;

	target_var = concat_args(tk);
	index = find_env_var(g_env->env_main, target_var);
	if (index == -1)
	{
		free(target_var);
		return (0);
	}
	remove_env(g_env->env_main, index);
	check_path_var(target_var);
	free(target_var);
	return (0);
}
