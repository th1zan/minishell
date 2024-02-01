/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_fd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:40:14 by thibault          #+#    #+#             */
/*   Updated: 2024/02/01 15:13:38 by thibault         ###   ########.fr       */
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

// Vérifie la présence de chevrons entre les tokens
int	out_pipe_cmd(t_tk *start, t_tk *end)
{
	t_tk	*tmp;

	tmp = start->next;
	while (tmp && tmp->type != TK_PIPE)
	{
		if (tmp->type == TK_APP_CHEVRON || tmp->type == TK_OUT_CHEVRON)
			return (1);
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
	return (0);
}

int	in_pipe_cmd(t_tk *start, t_tk *end)
{
	t_tk	*tmp;

	tmp = start->next;
	while (tmp && tmp->type != TK_PIPE)
	{
		if (tmp->type == TK_IN_CHEVRON)
			return (1);
		if (tmp == end)
			break ;
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
	while (tmp)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			prev_pipe = get_prev_pipe_tk(tmp);
			next_pipe = get_next_pipe_tk(tmp);
			set_cmd_fd_in(tmp, prev_pipe, next_pipe);
			set_cmd_fd_out(tmp, prev_pipe, next_pipe);
		}
		tmp = tmp->next;
	}
	return (0);
}
