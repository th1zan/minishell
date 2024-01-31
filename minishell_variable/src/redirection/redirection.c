/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:34:44 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 20:59:50 by zsoltani         ###   lausanne.ch       */
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
