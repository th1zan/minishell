/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:05:10 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 10:14:18 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status_error(char *arg)
{
	int	status;

	if (is_str_with_alpha(arg) || !is_all_digit(arg))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		status = 255;
		return (status);
	}
	else
	{
		status = ft_atoi(arg);
		if (status < 0)
			status = 256 + (status % 256);
		else
			status = status % 256;
		return (status);
	}
}

int	exit_builtin(t_tk *cmd)
{
	int	status;

	status = 0;
	ft_putstr_fd("exit\n", 2);
	if (cmd->tk_arg)
	{
		if (cmd->tk_arg->next)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
		{
			status = exit_status_error(cmd->tk_arg->tk_str);
		}
	}
	return (status);
}

int	is_str_with_alpha(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (ft_isalpha(*str))
			return (1);
		str++;
	}
	return (0);
}

int	is_all_digit(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}
