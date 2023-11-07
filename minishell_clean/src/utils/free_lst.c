/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:47:38 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:19:29 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_env(t_env *env)
{
	if (env)
	{
		if (env->env_main)
		{
			free_strtab_env(env->env_main);
			free(env->env_main);
		}
		if (env->path_tab)
		{
			free_strtab_env(env->path_tab);
			free(env->path_tab);
		}
		free(env);
	}
	return (0);
}

int	free_global_env(t_env *env)
{
	if (env)
	{
		if (g_env->env_main)
		{
			free_strtab_env(g_env->env_main);
			free(g_env->env_main);
		}
		if (g_env->path_tab)
		{
			free_strtab_env(g_env->path_tab);
			free(g_env->path_tab);
		}
		if (g_env->tk_head)
		{
			free_lst(g_env->tk_head);
			g_env->tk_head = NULL;
		}
		if (env->minishell_directory)
			free(env->minishell_directory);
	}
	free(env);
	return (0);
}

int	free_lst(t_tk *head_list)
{
	t_tk	*tmp;

	tmp = head_list;
	while (head_list)
	{
		tmp = head_list->next;
		free_elem(head_list);
		free(head_list);
		head_list = tmp;
	}
	return (0);
}

int	free_elem(t_tk *token)
{
	t_tk	*tmp;
	t_tk	*tmp_arg;

	if (token->tk_str)
	{
		free(token->tk_str);
		token->tk_str = NULL;
	}
	if (token->tk_arg)
	{
		tmp = token->tk_arg;
		while (tmp != NULL)
		{
			tmp_arg = tmp->next;
			if (tmp->tk_str)
				free(tmp->tk_str);
			free(tmp);
			tmp = tmp_arg;
		}
	}
	return (0);
}
