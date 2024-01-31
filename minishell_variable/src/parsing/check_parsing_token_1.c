/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_token_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:45:21 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 21:48:52 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_input_file(t_tk *tk, t_env *env)
{
	while (tk != NULL)
	{
		if (tk->type == TK_IN_CHEVRON)
		{
			if (!tk->tk_arg)
			{
				report_syntax_error(env, "newline");
				g_status = 258;
				return (1);
			}
			if (access(tk->tk_arg->tk_str, R_OK) == 0)
				return (0);
			else
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tk->tk_arg->tk_str, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_status = 1;
				return (1);
			}
		}
		tk = tk->next;
	}
	return (0);
}

int	check_cmd(t_tk *tk)
{
	while (tk != NULL)
	{
		if (tk->type == TK_CMD && test_cmd(tk) == FAILURE)
			return (1);
		tk = tk->next;
	}
	return (SUCCESS);
}

void	cmd_err(int status, char *cmd)
{
	if (status == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found \n", 2);
	}
	else if (status == 126)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}
