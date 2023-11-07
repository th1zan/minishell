/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_gramm_utils_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:09:33 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:09:49 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_here_doc_arg(t_tk *tk)
{
	t_tk	*tmp;

	tmp = tk;
	while (tmp)
	{
		if ((tmp->type == TK_APP_CHEVRON || tmp->type == TK_IN_CHEVRON
				|| tmp->type == TK_OUT_CHEVRON) && !tmp->tk_arg)
		{
			report_syntax_error("newline");
			return (258);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_main_list_tokens(t_tk *tk)
{
	t_tk	*tmp;
	t_tk	*prev;

	tmp = tk->next;
	prev = tk;
	while (tmp != NULL)
	{
		if ((prev->type == TK_CMD
				|| prev->type == TK_CMD_BUILT_IN) && !(is_tk_redir(tmp->type)
				|| tmp->type == TK_PIPE))
			return (131);
		if (is_tk_redir(prev->type) && !(tmp->type == TK_CMD
				|| tmp->type == TK_CMD_BUILT_IN || tmp->type == TK_FILE
				|| tmp->type == TK_ARG || is_tk_redir(tmp->type)
				|| tmp->type == TK_PIPE))
			return (132);
		if ((prev->type == TK_FILE || prev->type == TK_ARG)
			&& !(tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN))
			return (133);
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	check_redir_sublist(t_tk *tk)
{
	if (tk->tk_arg == NULL || tk->tk_arg->next != NULL)
	{
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putstr_fd("near unexpected token `newline'\n", 2);
		return (1);
	}
	if (tk->tk_arg->type != TK_FILE)
	{
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putstr_fd("near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}
