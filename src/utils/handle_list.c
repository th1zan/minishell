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
	if (tk->prev == NULL)
	{
		printf("\n-----PRINT LST--------\n");
	}
	// Print list
	while (tk != NULL)
	{
		
		fprintf(stderr,"%-15s ||", tk->tk_str);
		fprintf(stderr," tk_addr: %-15p", tk);
		fprintf(stderr," tk_type: %-5d", tk->type);
		fprintf(stderr," fd_in: %-5d", tk->fd_in);
		fprintf(stderr," fd_out: %-5d", tk->fd_out);
		// fprintf(stderr," prev_tk: %-15p", tk->prev);
		fprintf(stderr," next_tk: %-15p\n", tk->next);
		// Print sublist
		if (tk->tk_arg)
		{
			fprintf(stderr,"\n%-5s ----->PRINT ARG--------\n", "");
			print_lst(tk->tk_arg);
		}
		if (tk->next == NULL)
		{
			if (tk->type == TK_FILE || tk->type == TK_ARG)
			{
				fprintf(stderr,"\n%-5s ----->END PRINT ARG------\n\n", "");
			}
			else
			{
				fprintf(stderr,"\n-----END PRINT LST--------\n\n");
			}
		}
		tk = tk->next;
	}
	return (1);
}

int	free_lst(t_tk *head_list)
{
	t_tk	*tmp;

	while (head_list != NULL)
	{
		tmp = head_list->next;
		free_elem(head_list);
		head_list = tmp;
	}
	return (0);
}

int	free_elem(t_tk *token)
{
	t_tk	*tmp;
	// free tk_str
	if(token->tk_str)
		free(token->tk_str);
	// free tk_arg
	if(token->tk_arg)
	{
		tmp = token->tk_arg;
		while (tmp != NULL)
		{
			t_tk *next_tmp = tmp->next; // save next tk
			free_elem(tmp); // free current
			tmp = next_tmp; // current = next tk
		}
	}
	free(token);
	return (0);
}


// typedef struct s_tk
// {
// 	char		*tk;
// 	char		*type;
// 	char		*tk_arg_str;
// 	struct s_tk	*tk_arg;
// 	struct s_tk	*prev;
// 	struct s_tk	*next;
// }	t_tk;

// TEST Minishell
// < "file entree.txt" wc -l ||         ls  -l << 'output de sortie'