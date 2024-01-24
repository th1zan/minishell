/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:27:26 by mlachat           #+#    #+#             */
/*   Updated: 2023/11/03 10:05:38 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_built_in(t_tk *tk)
{
	int	fd_out;

	if (*(tk->env) == 0)
		return (1);
	fd_out = tk->fd_out;
	print_strtab(g_env->env_main, fd_out);
	return (0);
}

int	pwd(t_tk *tk)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, tk->fd_out);
	ft_putstr_fd("\n", tk->fd_out);
	return (0);
}
