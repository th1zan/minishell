/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:24:48 by thibault          #+#    #+#             */
/*   Updated: 2023/11/02 18:45:59 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_tk_str(t_tk *tk, char *fct_name)
{
	char	*cmd_str;
	int		len;

	cmd_str = tk->tk_str;
	len = ft_strlen(fct_name);
	if (ft_strncmp(cmd_str, fct_name, len) == 0)
		return (1);
	return (0);
}

int	is_echo(t_tk *tk)
{
	return (is_tk_str(tk, "echo"));
}

int	is_export(t_tk *tk)
{
	return (is_tk_str(tk, "export"));
}

int	is_unset(t_tk *tk)
{
	return (is_tk_str(tk, "unset"));
}

int	is_env(t_tk *tk)
{
	return (is_tk_str(tk, "env"));
}
