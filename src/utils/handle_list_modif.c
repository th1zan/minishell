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

void	ft_lst_modif_tk(t_tk *tk, void (*f)(void *))
{
	if (!(tk) || !(f))
		return ;
	while (tk)
	{
		(f)(tk->tk_str);
		tk = tk->next;
	}
}

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
/*
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!(lst) || !(f))
		return ;
	while (lst)
	{
		(f)(lst->content);
		lst = lst->next;
	}
}

typedef struct s_tk
{
	char		*tk_str;
	char		*type;
	char		*tk_arg_str;
	struct s_tk	*tk_arg;
	struct s_tk	*prev;
	struct s_tk	*next;
}	t_tk;

*/