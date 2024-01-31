/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:44:52 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 21:33:31 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(t_env *env_struct, int index)
{
	char	**env;
	char	**new_env;
	int		i;
	int		j;

	env = env_struct->env_main;
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
	env_struct->env_main = new_env;
}

void	check_path_var(t_env *env, char *var)
{
	if (!ft_strncmp(var, "PATH", 4))
	{
		free(env->path_tab);
		env->path_tab = get_path_tab(env->env_main);
	}
}

int	unset(t_tk *tk)
{
	char	*target_var;
	int		index;

	target_var = concat_args(tk);
	index = find_env_var(tk->env_struct->env_main, target_var);
	if (index == -1)
	{
		free(target_var);
		return (0);
	}
	remove_env(tk->env_struct, index);
	check_path_var(tk->env_struct, target_var);
	free(target_var);
	return (0);
}
