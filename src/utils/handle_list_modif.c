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
		if (is_tk_in_out_app(tk->type) || tk->type == TK_PIPE || tk->type == TK_HERE_DOC)
			prev_classified_tk = tk->type;
		// printf("IN-> tr:%s type: %d, prev_classified_tk:%d \n", tk->tk_str, tk->type, prev_classified_tk);
		if (tk->type == TK_UNCLASSIFIED)
		{
			// printf("INSIDE IF-> %s type: %d\n", tk->tk_str, tk->type);
			if (tk->prev == NULL || prev_classified_tk == TK_BLANK)
				tk->type = TK_CMD;
			else if (prev_classified_tk == TK_PIPE)
				tk->type = TK_CMD;
			else if (tk->prev->type == TK_FILE && is_tk_in_out_app(prev_classified_tk))
				tk->type = TK_CMD;
			else if (tk->prev->type == TK_CMD)
				tk->type = TK_CMD;
			else if (tk->prev->type == TK_HD_ARG)
				tk->type = TK_CMD;
			else if (is_tk_in_out_app(prev_classified_tk))
				tk->type = TK_FILE;	
			else if (prev_classified_tk == TK_HERE_DOC)
				tk->type = TK_HD_ARG;
		}
		// printf("OUT-> %s type: %d \n", tk->tk_str, tk->type);
		tk = tk->next;
	}
}

int ft_delete_type_token(t_tk **tk, int tk_type)
{
	t_tk	*tmp;

	if (!(*tk))
		return (1);
	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == tk_type)
		{
			// printf("remove token %p\n", tmp);
			if (tmp->prev == NULL)
				*tk = tmp->next;
			tmp = ft_lst_remove(tmp);
			// printf("token deleted !\n");
		}
		else
			tmp = tmp->next;			
	}

		return (0);
}
