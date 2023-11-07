/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:26:16 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:19:54 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mv_arg_to_sublst(t_tk **tmp, t_tk **sub_last, t_tk *cmd, t_tk **last)
{
	t_tk	*next;

	next = (*tmp)->next;
	if ((*tmp)->prev)
		(*tmp)->prev->next = (*tmp)->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = (*tmp)->prev;
	if (*sub_last)
	{
		(*tmp)->prev = *sub_last;
		(*sub_last)->next = *tmp;
	}
	else
	{
		cmd->tk_arg = *tmp;
		(*tmp)->prev = NULL;
	}
	(*tmp)->next = NULL;
	*sub_last = *tmp;
	if (*last && (*last)->type != TK_ARG)
		(*last)->next = next;
	*tmp = next;
}

t_tk	*handle_command(t_tk **cmd, t_tk **tmp, t_tk **last, t_tk **sub_last)
{
	*cmd = *tmp;
	*last = *tmp;
	*sub_last = NULL;
	*tmp = (*tmp)->next;
	while (*tmp && (*tmp)->type != TK_PIPE)
	{
		if ((*tmp)->type == TK_ARG)
		{
			mv_arg_to_sublst(tmp, sub_last, *cmd, last);
			handle_quotes(*tmp);
		}
		else
		{
			*last = *tmp;
			*tmp = (*tmp)->next;
		}
	}
	return (*tmp);
}

t_tk	*move_args_to_sublist(t_tk *tk)
{
	t_tk	*tmp;
	t_tk	*cmd;
	t_tk	*last;
	t_tk	*sub_last;

	tmp = tk;
	cmd = NULL;
	last = NULL;
	sub_last = NULL;
	while (tmp)
	{
		if (tmp->type == TK_CMD)
			tmp = handle_command(&cmd, &tmp, &last, &sub_last);
		else if (tmp && tmp->type == TK_PIPE)
		{
			last = tmp;
			tmp = tmp->next;
		}
	}
	return (tk);
}
