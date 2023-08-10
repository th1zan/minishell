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


t_tk	*ft_lstlast(t_tk *tk)
{
	if (!tk)
		return (0);
	while (tk->next != 0)
		tk = tk->next;
	return (tk);
}

int	ft_lstsize(t_tk *tk)
{
	int	n;

	n = 0;
	while (tk != 0)
	{
		tk = tk->next;
		n++;
	}
	return (n);
}

int	print_lst(t_tk *tk)
{
	if (!tk)
	{
		ft_putstr_fd("tk vide\n", 1);
		return (0);
	}
	ft_putstr_fd("\n", 1);
	while (tk != 0)
	{
		printf("%s\n",tk->tk);
		printf("%p\n",tk->next);
		tk = tk->next;
	}
	return (0);
}

int	free_lst(t_tk *head_list)
{
	t_tk	*tmp;

	while (head_list != NULL)
	{
		tmp = head_list->next;
		// free attributs
		free(head_list->tk);
		free(head_list->type);
		free(head_list->str_arg);
		// free element
		free(head_list);
		head_list = tmp;
	}
	return (0);
}
