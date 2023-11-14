/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_gramm_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:06:36 by thibault          #+#    #+#             */
/*   Updated: 2023/11/14 11:47:13 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_last_token(t_tk *first, t_tk *last)
{
	if (!(is_tk_redir(first->type)
			|| first->type == TK_CMD || first->type == TK_CMD_BUILT_IN))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(first->tk_str, 2);
		ft_putstr_fd("'\n", 2);
		g_env->status = 258;
		return (1);
	}
	if (!(is_tk_redir(last->type) || last->type == TK_CMD
			|| first->type == TK_CMD_BUILT_IN || last->type == TK_PIPE))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(first->tk_str, 2);
		ft_putstr_fd("'\n", 2);
		g_env->status = 258;
		return (1);
	}
	return (0);
}

void	report_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	g_env->status = 258;
}

int	check_cmd_after_pipe(t_tk *tk)
{
	while (tk)
	{
		if (tk->type == TK_PIPE && !(get_next_type_tk(tk, TK_CMD)
				|| get_next_type_tk(tk, TK_CMD_BUILT_IN)))
		{
			report_syntax_error("|");
			return (258);
		}
		else if (tk->type == TK_HERE_DOC
			&& ft_strncmp(tk->tk_str, "<<", 2) == 0)
		{
			report_syntax_error("newline");
			return (258);
		}
		tk = tk->next;
	}
	return (0);
}
