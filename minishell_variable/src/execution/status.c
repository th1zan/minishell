/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:13:41 by thibault          #+#    #+#             */
/*   Updated: 2024/01/27 16:35:29 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_replace(char **env, char *new_var, int index)
{
	free(env[index]);
	env[index] = new_var;
}

char	**create_new_env(char **env, char *new_var, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc((size + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[0] = new_var;
	i = -1;
	while (++i < size)
		new_env[i + 1] = env[i];
	new_env[size + 1] = NULL;
	return (new_env);
}

int	save_status_var_in_env(t_env *env_tk)
{
	char	*new_var;
	int		index;
	int		size;

	new_var = ft_strjoin("?=", ft_itoa(env_tk->status));
	if (!new_var)
		return (-1);
	index = find_env_var(env_tk->env_main, "?");
	if (index != -1)
		free_and_replace(env_tk->env_main, new_var, index);
	else
	{
		size = 0;
		while (env_tk->env_main[size])
			size++;
		env_tk->env_main = create_new_env(env_tk->env_main, new_var, size);
		if (!env_tk->env_main)
			return (-1);
	}
	return (0);
}

int	update_status_variable(t_env *env, int bin_status, int status_built_in)
{
	t_tk	*tmp;

	tmp = ft_lstlast(env->tk_head);
	if (status_built_in != 0 && tmp->type == TK_CMD_BUILT_IN)
	{
		// env->status = status_built_in;
		g_status = status_built_in;
		// printf("update_status_variable:: status_built_in %d, g_status %d\n", status_built_in, g_status);
		return (status_built_in);
	}
	else if (bin_status != 0 && tmp->type == TK_CMD)
	{
		// env->status = bin_status;
		g_status = bin_status;
		// printf("update_status_variable:: bin_status %d, g_status %d\n", bin_status, g_status);
		return (bin_status);
	}
	// env->status = 0;
	// g_status = 0;
	return (0);
}
