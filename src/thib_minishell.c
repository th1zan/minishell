/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/08/15 12:07:55 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tk	*tk_head;
	(void)argc;
	(void)argv;
	(void)envp;

	tk_head = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (check_input(input))
			break;
		// get_delimiter(input);
		input_to_token(input, &tk_head, get_delimiter(input));
		// print_lst(tk_head);
		parse_token(&tk_head);
		// printf("Vous avez entré : %s\n", input);
		// if (is_redir_in(input, 0))
		// 	printf("is < \n");
		// free(input);
	}
	return(0);
}

int	check_input(char *input)
{
	if (input == NULL)
		return(1);
	if (*input == 0)
		return (1);
	return (0);
}

int	ft_coucou(void)
{
	ft_printf("Coucou depuis le fichier minishell.c !\net ...\n");
	return (0);
}