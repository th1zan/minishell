/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:34:44 by thibault          #+#    #+#             */
/*   Updated: 2024/02/01 15:15:56 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_redirection(t_tk **tk)
{
	if (set_default_fd(tk))
		return (-1);
	if (set_pipe_fd(tk))
		return (-1);
	if (set_input_operator_fd(tk))
		return (-1);
	if (set_output_operator_fd(tk))
		return (-1);
	if (set_cmd_std_fd(tk))
		return (-1);
	if (set_cmd_operator_fd(tk))
		return (-1);
	if (set_cmd_pipe_fd(tk))
		return (-1);
	if (redir_operator_fd(tk))
		return (-1);
	return (0);
}

int	redir_operator_fd(t_tk **tk)
{
	t_tk	*current;
	int		result;

	current = *tk;
	while (current != NULL)
	{
		result = process_redirection(current);
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (0);
}

void	set_cmd_fd_in(t_tk *tmp, t_tk *prev_pipe, t_tk *next_pipe)
{
	if (prev_pipe)
	{
		if (!in_pipe_cmd(prev_pipe, tmp)
			&& !(next_pipe && in_pipe_cmd(tmp, next_pipe))
			&& !(!next_pipe && in_pipe_cmd(tmp, ft_lstlast(tmp))))
		{
			tmp->fd_in = prev_pipe->fd_out;
		}
	}
}

void	set_cmd_fd_out(t_tk *tmp, t_tk *prev_pipe, t_tk *next_pipe)
{
	if (next_pipe)
	{
		if (!out_pipe_cmd(tmp, next_pipe)
			&& !(prev_pipe && out_pipe_cmd(prev_pipe, tmp))
			&& !(!prev_pipe && out_pipe_cmd(ft_lstfirst(tmp), tmp)))
		{
			tmp->fd_out = next_pipe->fd_in;
		}
	}
}
