/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:13:41 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 21:44:23 by zsoltani         ###   lausanne.ch       */
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

t_tk	*get_prev_cmd_tk(t_tk *tk)
{
	t_tk	*tmp;

	if (!tk)
		return (tk);
	tmp = tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
			return (tmp);
		tmp = tmp->prev;
	}
	return (tk);
}

int	update_status_variable(t_env *env, int bin_status, int status_built_in)
{
	t_tk	*tmp;

	tmp = ft_lstlast(env->tk_head);
	tmp = get_prev_cmd_tk(tmp);
	if (status_built_in != 0 && tmp->type == TK_CMD_BUILT_IN)
	{
		g_status = status_built_in;
		return (status_built_in);
	}
	else if (bin_status != 0 && tmp->type == TK_CMD)
	{
		g_status = bin_status;
		return (bin_status);
	}
	g_status = 0;
	return (0);
}
