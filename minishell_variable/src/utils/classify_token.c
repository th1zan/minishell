/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:52:44 by thibault          #+#    #+#             */
/*   Updated: 2023/11/06 12:20:14 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	classify_token_operator(t_tk *tmp)
{
	if (tmp->prev && tmp->prev->type == TK_HERE_DOC)
		tmp->type = TK_HD_ARG;
	else if (tmp->prev == NULL
		|| tmp->prev->type == TK_BLANK || tmp->prev->type == TK_PIPE)
		tmp->type = TK_CMD;
	else if (tmp->prev->type == TK_APP_CHEVRON
		|| tmp->prev->type == TK_IN_CHEVRON
		|| tmp->prev->type == TK_OUT_CHEVRON)
		tmp->type = TK_FILE;
}

void	classify_token_type(t_tk *tk)
{
	t_tk	*tmp;

	tmp = tk;
	while (tmp)
	{
		if (tmp->type == TK_UNCLASSIFIED)
			classify_token_operator(tmp);
		tmp = tmp->next;
	}
	tmp = tk;
	while (tmp)
	{
		if (tmp->type == TK_UNCLASSIFIED)
			tmp->type = TK_CMD;
		tmp = tmp->next;
	}
}

void	ft_lst_classify_tk_unclassified(t_tk *tk)
{
	t_tk	*tmp;

	if (!tk)
		return ;
	tmp = tk;
	classify_token_type(tmp);
}
