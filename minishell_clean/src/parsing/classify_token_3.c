/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token_3                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:07:15 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:07:28 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_hd_arg_tk(t_tk *tk)
{
	char	*temp_file_path;
	int		result;

	temp_file_path = NULL;
	while (tk != NULL)
	{
		result = process_hd_arg(tk, &temp_file_path);
		if (result == -1)
		{
			free_memory_and_close_fd(&tk->fd_in, &temp_file_path);
			return (1);
		}
		tk = tk->next;
	}
	return (0);
}

int	ft_handle_file_tk(t_tk *tk)
{
	t_tk	*tk_file;

	if (!(tk))
		return (1);
	while (tk)
	{
		if (is_tk_in_out_app(tk->type) && tk->next)
		{
			tk_file = tk->next;
			tk_file->type = TK_FILE;
			tk->next = tk_file->next;
			tk->tk_arg = tk_file;
			if (tk_file->next)
				tk_file->next->prev = tk;
			tk_file->next = NULL;
		}
		tk = tk->next;
	}
	return (0);
}

int	ft_handle_built_in(t_tk *tk)
{
	t_tk	*tmp;

	if (!(tk))
		return (1);
	tmp = tk;
	while (tmp)
	{
		if (tmp->type == TK_CMD)
		{
			if (is_builtin_cmd_tk(tmp) == 1)
				tmp->type = TK_CMD_BUILT_IN;
		}
		tmp = tmp->next;
	}
	return (0);
}
