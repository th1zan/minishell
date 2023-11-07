/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_token_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:45:21 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:17:33 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_input_file(t_tk *tk)
{
	while (tk != NULL)
	{
		if (tk->type == TK_IN_CHEVRON)
		{
			if (!tk->tk_arg)
			{
				report_syntax_error("newline");
				g_env->status = 258;
				return (1);
			}
			if (access(tk->tk_arg->tk_str, R_OK) == 0)
				return (0);
			else
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tk->tk_arg->tk_str, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_env->status = 1;
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
		fprintf(stderr, "minishell: %s: Command not found \n", cmd);
	else if (status == 126)
		fprintf(stderr, "minishell: %s: Permission denied\n", cmd);
}
