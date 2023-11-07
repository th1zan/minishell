/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:04:47 by thibault          #+#    #+#             */
/*   Updated: 2023/11/06 15:23:44 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_pipe_fd(t_tk **tk)
{
	t_tk		*tmp;
	int			pipe_tab[2];

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_PIPE)
		{
			if (pipe(pipe_tab) == -1)
			{
				perror("Failed to create the pipe");
				return (-1);
			}
			tmp->fd_in = pipe_tab[1];
			tmp->fd_out = pipe_tab[0];
		}
		tmp = tmp->next;
	}
	return (0);
}

int	duplicate_fd(int old_fd, int new_fd, char *error_message)
{
	if (fd_is_standard(old_fd) == 0)
	{
		if (dup2(old_fd, new_fd) == -1)
		{
			perror(error_message);
			return (-1);
		}
	}
	return (0);
}

int	handle_pipes(t_tk *tk)
{
	if (get_prev_type_tk(tk, TK_PIPE))
		if (duplicate_fd(tk->fd_in, STDIN_FILENO, "dup2 error: fd_in") == -1)
			return (-1);
	if (get_next_type_tk(tk, TK_PIPE) || (tk->next && tk->next->next
			&& tk->next->type == TK_HERE_DOC
			&& tk->next->next->type == TK_PIPE))
		if (duplicate_fd(tk->fd_out, STDOUT_FILENO, "dup2 error: fd_out") == -1)
			return (-1);
	return (0);
}

int	set_fd_for_pipe(t_tk *tk)
{
	if (handle_pipes(tk) == -1)
		return (-1);
	return (0);
}
