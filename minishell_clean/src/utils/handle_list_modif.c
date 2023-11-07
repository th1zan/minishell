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

void	ft_lst_replace_var(t_tk *tk, int (*f)(char **str, char ***env))
{
	if (!(tk) || !(f))
		return ;
	while (tk)
	{
		if ((f)(&tk->tk_str, tk->env) > -1)
		{
			if (tk->prev && (tk->prev->type == TK_BLANK))
				tk->is_var_type_with_space_before = 1;
		}
		tk = tk->next;
	}
}

int	ft_delete_type_token(t_tk **tk, int tk_type)
{
	t_tk	*tmp;

	if (!(*tk))
		return (1);
	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == tk_type)
		{
			if (tmp->prev == NULL)
				*tk = tmp->next;
			tmp = ft_lst_remove(tmp);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
