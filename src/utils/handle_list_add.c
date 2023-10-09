/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:23:09 by thibault          #+#    #+#             */
/*   Updated: 2023/10/09 15:38:16 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tk *ft_lstnew(char *token_str, char **path, char ***envp)
{
	t_tk *new_tk;

	new_tk = (t_tk *)calloc(1, sizeof(t_tk));
	if (!new_tk)
		return (NULL);
	new_tk->tk_str = token_str;
	new_tk->path_tab = path;
	new_tk->env = envp;
	return (new_tk);
}

void	ft_lstadd_back(t_tk **head_tk_tk, t_tk *new_tk)
{
	t_tk	*tk_end;

	tk_end = ft_lstlast(*head_tk_tk);
	if (tk_end == 0)
		*head_tk_tk = new_tk;
	else
	tk_end->next = new_tk;
	new_tk->prev = tk_end;
}

t_tk	*ft_lst_remove(t_tk *current_tk)
{
	t_tk	*tmp;

	tmp = NULL;
	// If prev and next token exist
	if (current_tk->prev && current_tk->next)
	{
		tmp = current_tk->next;
		current_tk->prev->next = current_tk->next;
		current_tk->next->prev = current_tk->prev;
	}
	
	// If prev and not next token exist
	else if (current_tk->prev && !current_tk->next)
	{
		current_tk->prev->next = NULL;
	}
	
	// HEAD TOKEN -> If not prev and next token exist
	else if (!current_tk->prev && current_tk->next)
	{
		current_tk->next->prev = NULL;
		tmp = current_tk->next;
	}

	// If not prev and not next token exist -> NOTHING

	// then free current_tk
	free_elem(current_tk);
	return (tmp);
}

