/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:52 by thibault          #+#    #+#             */
/*   Updated: 2023/08/10 09:35:52 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_modif_tk_str(t_tk *tk, int (*f)(char **str))
{
	if (!(tk) || !(f))
		return ;
	while (tk)
	{
		(f)(&tk->tk_str);
		tk = tk->next;
	}
}

void	ft_lst_modif_tk_type(t_tk *tk, int (*f)(char *str))
{
	if (!(tk) || !(f))
		return ;
	while (tk)
	{
		tk->type = (f)(tk->tk_str);
		tk = tk->next;
	}
}

void	ft_lst_classify_tk_file(t_tk *tk)
{
	int prev_classified_tk;
	
	if (!(tk))
		return;
	prev_classified_tk = tk->type;
	while (tk)
	{
		if (check_file_operator(tk->type) || tk->type == TOKEN_PIPE || tk->type == TOKEN_HERE_DOC)
			prev_classified_tk = tk->type;
		// printf("IN-> tr:%s type: %d, prev_classified_tk:%d \n", tk->tk_str, tk->type, prev_classified_tk);
		if (tk->type == TOKEN_UNCLASSIFIED)
		{
			// printf("INSIDE IF-> %s type: %d\n", tk->tk_str, tk->type);
			if (tk->prev == NULL || prev_classified_tk == TOKEN_BLANK)
				tk->type = TOKEN_COMMAND;
			else if (prev_classified_tk == TOKEN_PIPE)
				tk->type = TOKEN_COMMAND;
			else if (tk->prev->type == TOKEN_FILE && check_file_operator(prev_classified_tk))
				tk->type = TOKEN_COMMAND;
			else if (tk->prev->type == TOKEN_COMMAND)
				tk->type = TOKEN_COMMAND;
			else if (check_file_operator(prev_classified_tk))
				tk->type = TOKEN_FILE;	
			else if (prev_classified_tk == TOKEN_HERE_DOC)
				tk->type = TOKEN_HD_ARG;
		}
		// printf("OUT-> %s type: %d \n", tk->tk_str, tk->type);
		tk = tk->next;
	}
}
