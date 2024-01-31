/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_fd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:46:18 by zsoltani          #+#    #+#             */
/*   Updated: 2024/01/30 20:56:29 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_fd_in(t_tk *tmp)
{
	t_tk	*input_operator;

	input_operator = get_prev_input_operator_tk(tmp);
	if (input_operator == NULL)
		input_operator = get_next_input_operator_tk(tmp);
	if (input_operator != NULL)
		tmp->fd_in = input_operator->fd_in;
	else
		tmp->fd_in = 0;
}

void	set_fd_out(t_tk *tmp)
{
	t_tk	*output_operator;

	output_operator = get_prev_output_operator_tk(tmp);
	if (output_operator == NULL)
		output_operator = get_next_output_operator_tk(tmp);
	if (output_operator != NULL)
		tmp->fd_out = output_operator->fd_out;
	else
		tmp->fd_out = 1;
}

int	set_cmd_operator_fd(t_tk **tk)
{
	t_tk	*tmp;

	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			set_fd_in(tmp);
			set_fd_out(tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
