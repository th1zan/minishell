/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:56:11 by thibault          #+#    #+#             */
/*   Updated: 2023/11/14 13:36:29 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_args(t_tk *tk, t_tk *tmp, int newline)
{
	// fprintf(stderr, "fd_out %d\n", tk->fd_out);
	while (tmp)
	{
		if (!is_blank_str(tmp->tk_str))
			ft_putstr_fd(tmp->tk_str, tk->fd_out);
		tmp = tmp->next;
		if ((tmp) && tmp->is_var_type_with_space_before)
			ft_putstr_fd(" ", tk->fd_out);
	}
	if (newline)
		ft_putstr_fd("\n", tk->fd_out);
}

int	echo(t_tk *tk)
{
	t_tk	*tmp;
	int		newline;

	tmp = tk->tk_arg;
	if (!(tmp))
	{
		ft_putstr_fd("\n", tk->fd_out);
		return (0);
	}
	newline = ft_strncmp(tmp->tk_str, "-n", 2) != 0;
	if (!newline)
		tmp = tmp->next;
	// fprintf(stderr, "fd_out %d\n", tk->fd_out);
	// print_lst(g_env->tk_head);
	print_args(tk, tmp, newline);
	return (0);
}
