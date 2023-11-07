/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:18:26 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_tk **head_tk)
{
	ft_lst_modif_tk_str(*head_tk, del_whitespace);
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	ft_lst_replace_var(*head_tk, replace_with_values);
	ft_delete_type_token(head_tk, TK_BLANK);
	ft_lst_classify_tk_unclassified(*head_tk);
	ft_handle_hd_arg_tk(*head_tk);
	ft_handle_file_tk(*head_tk);
	ft_handle_arg_tk(*head_tk);
	ft_handle_built_in(*head_tk);
	if (check_cmd(*head_tk))
		return (-1);
	handle_quotes(*head_tk);
	ft_delete_type_token(head_tk, TK_HD_ARG);
	if (check_input_file(*head_tk))
		return (-1);
	return (0);
}

int	check_parsing(t_tk *tk)
{
	int	check;

	check = 0;
	check = check_grammar(tk);
	if (check > 0)
	{
		g_env->error_parsing = check;
		return (check);
	}
	return (0);
}

int	handle_quotes(t_tk *head_tk)
{
	t_tk	*tmp;
	char	*tmp_str;

	tmp = head_tk;
	while (tmp)
	{
		tmp_str = tmp->tk_str;
		tmp->tk_str = remove_quotes(tmp->tk_str);
		free(tmp_str);
		if (tmp->tk_arg)
			handle_quotes(tmp->tk_arg);
		tmp = tmp->next;
	}
	return (0);
}
