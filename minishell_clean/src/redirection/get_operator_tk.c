/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_tk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:47:09 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 14:08:25 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tk	*get_next_input_operator_tk(t_tk *tk)
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
		if (tmp->type == TK_IN_CHEVRON || tmp->type == TK_HERE_DOC)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_tk	*get_prev_input_operator_tk(t_tk *tk)
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
		if (tmp->type == TK_IN_CHEVRON || tmp->type == TK_HERE_DOC)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_tk	*get_next_output_operator_tk(t_tk *tk)
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
		if (tmp->type == TK_OUT_CHEVRON || tmp->type == TK_APP_CHEVRON)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_tk	*get_prev_output_operator_tk(t_tk *tk)
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
		if (tmp->type == TK_OUT_CHEVRON || tmp->type == TK_APP_CHEVRON)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}
