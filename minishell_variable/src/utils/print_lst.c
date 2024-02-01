/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:46:11 by thibault          #+#    #+#             */
/*   Updated: 2024/02/01 15:15:33 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tk_details(t_tk *tk)
{
	fprintf(stderr, "%-15s ||", tk->tk_str);
	fprintf(stderr, " tk_addr: %-15p", tk);
	fprintf(stderr, " tk_type: %-5d", tk->type);
	fprintf(stderr, " fd_in: %-5d", tk->fd_in);
	fprintf(stderr, " fd_out: %-5d", tk->fd_out);
	fprintf(stderr, " prev_tk: %-15p", tk->prev);
	fprintf(stderr, " next_tk: %-15p", tk->next);
	fprintf(stderr, " sub_tk: %-15p\n", tk->tk_arg);
}

int	print_lst(t_tk *tk)
{
	if (!tk)
	{
		ft_putstr_fd("tk vide\n", 1);
		return (0);
	}
	if (tk->prev == NULL)
		printf("\n-----PRINT LST--------\n");
	while (tk != NULL)
	{
		print_tk_details(tk);
		if (tk->tk_arg)
		{
			fprintf(stderr, "\n%-5s ----->PRINT ARG--------\n", "");
			print_lst(tk->tk_arg);
		}
		if (tk->next == NULL)
		{
			if (tk->type == TK_FILE || tk->type == TK_ARG)
				fprintf(stderr, "\n%-5s ----->END PRINT ARG------\n\n", "");
			else
				fprintf(stderr, "\n-----END PRINT LST--------\n\n");
		}
		tk = tk->next;
	}
	return (1);
}
