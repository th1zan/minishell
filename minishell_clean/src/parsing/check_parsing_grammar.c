/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_grammar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:42:49 by thibault          #+#    #+#             */
/*   Updated: 2023/11/14 11:09:20 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prt_err(char *message, int status, int return_value)
{
	ft_putstr_fd("minishell: error: ", 2);
	ft_putstr_fd(message, 2);
	g_env->status = status;
	return (return_value);
}

int	check_input_redirect(t_tk *tmp)
{
	if (tmp->type == TK_IN_CHEVRON && tmp->next
		&& (tmp->next->type == TK_IN_CHEVRON || tmp->next->type == TK_HERE_DOC))
		ft_lst_remove(tmp);
	return (0);
}

int	check_output_redirect(t_tk *tmp)
{
	if ((tmp->type == TK_OUT_CHEVRON || tmp->type == TK_APP_CHEVRON)
		&& tmp->next && (tmp->next->type == TK_OUT_CHEVRON
			|| tmp->next->type == TK_APP_CHEVRON))
		ft_lst_remove(tmp);
	return (0);
}

int	validate_tokens(t_tk *tk)
{
	int	check;

	check = 0;
	while (tk != NULL)
	{
		if (is_tk_in_out_app(tk->type))
		{
			if (check_redir_sublist(tk))
				return (141);
			check = check_input_redirect(tk);
			if (check != 0)
				return (check);
			check = check_output_redirect(tk);
			if (check != 0)
				return (check);
		}
		tk = tk->next;
	}
	return (0);
}

int	check_grammar(t_tk *tk)
{
	int	check;

	check = 0;
	if (!tk)
		return (prt_err("error - no argument\n", 11, 11));
	check = check_here_doc_arg(tk);
	if (check != 0)
		return (check);
	check = check_cmd_after_pipe(tk);
	if (check != 0)
		return (check);
	check = check_first_last_token(tk, tk);
	if (check != 0)
		return (check);
	check = check_main_list_tokens(tk);
	if (check != 0)
		return (check);
	return (validate_tokens(tk));
}
