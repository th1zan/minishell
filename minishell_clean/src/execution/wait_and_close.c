/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:11:53 by mlachat           #+#    #+#             */
/*   Updated: 2023/11/03 12:20:10 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_is_standard(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return (1);
	return (0);
}

int	close_all_fd(t_tk **tk)
{
	t_tk	*tmp;

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			if ((tmp->fd_in != -1) && (fd_is_standard(tmp->fd_in) != 1))
			{
				if (close(tmp->fd_in) == -1)
					perror("Error closing fd_in");
				tmp->fd_in = -1;
			}
			if ((tmp->fd_out != -1) && (fd_is_standard(tmp->fd_out) != 1))
			{
				if (close(tmp->fd_out) == -1)
					perror("Error closing fd_out");
				tmp->fd_out = -1;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	wait_all_pid(t_tk **tk)
{
	t_tk	*tmp;
	int		status;

	tmp = *tk;
	if (tmp->type != TK_CMD)
		tmp = get_next_type_tk(tmp, TK_CMD);
	status = 0;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		status = get_status_info(status);
		tmp = get_next_type_tk(tmp, TK_CMD);
	}
	return (status);
}

/*
convention bash: Si un programme est terminé par un signal,
alors le code de sortie sera `128 + numéro du signal`
*/

int	get_status_info(int status)
{
	if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
