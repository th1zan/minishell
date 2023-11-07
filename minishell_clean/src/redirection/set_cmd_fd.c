/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:40:14 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 13:56:23 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_cmd_std_fd(t_tk **tk)
{
	t_tk		*tmp;

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			if (tmp->prev == 0)
				tmp->fd_in = STDIN_FILENO;
			if (tmp->next == 0)
				tmp->fd_out = STDOUT_FILENO;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	set_cmd_pipe_fd(t_tk **tk)
{
	t_tk	*tmp;
	t_tk	*prev_pipe;
	t_tk	*next_pipe;

	tmp = *tk;
	while (tmp != NULL)
	{
		prev_pipe = get_prev_type_tk(tmp, TK_PIPE);
		next_pipe = get_next_type_tk(tmp, TK_PIPE);
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			if (prev_pipe)
				tmp->fd_in = prev_pipe->fd_out;
			if (next_pipe)
				tmp->fd_out = next_pipe->fd_in;
		}
		tmp = tmp->next;
	}
	return (0);
}

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
