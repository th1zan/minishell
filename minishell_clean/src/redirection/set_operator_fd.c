/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_operator_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:35:20 by thibault          #+#    #+#             */
/*   Updated: 2023/11/06 23:12:28 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_default_fd(t_tk **tk)
{
	t_tk		*tmp;

	tmp = *tk;
	while (tmp != NULL)
	{
		tmp->fd_in = -1;
		tmp->fd_out = -1;
		tmp = tmp->next;
	}
	return (0);
}

int	open_chevron_fd(t_tk *tmp, int flags)
{
	char	*file;

	file = tmp->tk_arg->tk_str;
	close(tmp->fd_out);
	tmp->fd_out = open_file_to_fd(file, flags);
	if (tmp->fd_out == -2)
		return (-1);
	return (0);
}

int	set_input_operator_fd(t_tk **tk)
{
	t_tk	*tmp;

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_IN_CHEVRON)
		{
			close(tmp->fd_in);
			tmp->fd_in = open_file_to_fd(tmp->tk_arg->tk_str, O_RDONLY);
			if (tmp->fd_in == -2)
				return (-1);
		}
		if (tmp->type == TK_HERE_DOC)
		{
			close(tmp->fd_in);
			tmp->fd_in = open_file_to_fd(tmp->tk_str, O_RDONLY);
			if (tmp->fd_in == -2)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	set_output_operator_fd(t_tk **tk)
{
	t_tk	*tmp;

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_OUT_CHEVRON)
		{
			if (open_chevron_fd(tmp, O_CREAT | O_WRONLY | O_TRUNC) == -1)
				return (-1);
		}
		else if (tmp->type == TK_APP_CHEVRON)
		{
			if (open_chevron_fd(tmp, O_CREAT | O_WRONLY | O_APPEND) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	open_file_to_fd(char *file, int option)
{
	int	fd;

	fd = open(file, option, 0777);
	if (fd == -1)
	{
		perror("minishell");
		return (-2);
	}
	return (fd);
}
