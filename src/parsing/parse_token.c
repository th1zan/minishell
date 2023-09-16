/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfinocie <vfinocie@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/09/16 14:02:51 by vfinocie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_tk **head_tk)
{
	// t_tk	*tmp;

	// tmp = *head_tk;
	// print_lst(*head_tk);
	ft_lst_modif_tk_str(*head_tk, del_whitespace); //this function, iterrates through the list, applying the del_whitespace function to each node. 
	// print_lst(*head_tk);
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	// print_lst(*head_tk);
	ft_delete_type_token(head_tk, TK_BLANK);
	// print_lst(*head_tk);
	ft_lst_classify_tk_file(*head_tk);
	// print_lst(*head_tk);
	/*TODO: vérification des règles de grammaire ex: deux operateur à la suite-> pas possible*/
	ft_handle_file_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_arg_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_hd_arg_tk(*head_tk);
	ft_delete_type_token(head_tk, TK_HD_DELIM);
	print_lst(*head_tk);
	check_parsing(*head_tk);
	// tmp = tmp->next;
	// print_strtab(tmp->env);
	printf("fin du parsing\n");

	return (0);
}

int		check_parsing(t_tk *tk)
{
	check_grammar(tk);
	check_cmd(tk);
	check_input_file(tk);

	return (0);
}


// TEST Minishell
// < "file entree.txt" wc -l |         ls  -l << 'output de sortie'