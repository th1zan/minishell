/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:54:07 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 21:15:11 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tk	*get_next_cmd(t_tk *tk)
{
	t_tk	*tmp;

	if (tk->next)
		tmp = tk->next;
	else
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_tk	*get_next_type_tk(t_tk *tk, int type)
{
	t_tk	*tmp;

	if (!tk)
		return (NULL);
	if (tk->next)
		tmp = tk->next;
	else
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->type == type)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_tk	*get_prev_type_tk(t_tk *tk, int type)
{
	t_tk	*tmp;

	if (!tk)
		return (NULL);
	if (tk->prev)
		tmp = tk->prev;
	else
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->type == type)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

// t_tk	*get_next_pipe_tk(t_tk *tk)
// {
// 	t_tk	*tmp;

// 	if (!tk)
// 		return (NULL);
// 	if (tk->next)
// 		tmp = tk->next;
// 	else
// 		return (NULL);
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type == TK_APP_CHEVRON || tmp->type == TK_OUT_CHEVRON)
// 			return (NULL);
// 		if (tmp->type == TK_PIPE)
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// t_tk	*get_prev_pipe_tk(t_tk *tk)
// {
// 	t_tk	*tmp;

// 	if (!tk)
// 		return (NULL);
// 	if (tk->prev)
// 		tmp = tk->prev;
// 	else
// 		return (NULL);
// 	while (tmp != NULL)
// 	{
// 		if (tmp->type == TK_APP_CHEVRON || tmp->type == TK_OUT_CHEVRON)
// 			return (NULL);
// 		if (tmp->type == TK_PIPE)
// 			return (tmp);
// 		tmp = tmp->prev;
// 	}
// 	return (NULL);
// }

// Retourne le prochain token de type pipe
t_tk	*get_next_pipe_tk(t_tk *tk)
{
	t_tk	*tmp;

	if (!tk)
		return (NULL);
	tmp = tk->next;
	while (tmp)
	{
		if (tmp->type == TK_PIPE)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// Retourne le token de pipe précédent
t_tk	*get_prev_pipe_tk(t_tk *tk)
{
	t_tk	*tmp;

	if (!tk)
		return (NULL);
	tmp = tk->prev;
	while (tmp)
	{
		if (tmp->type == TK_PIPE)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
