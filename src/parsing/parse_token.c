/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/08/24 16:44:49 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_tk **head_tk)
{
	// print_lst(*head_tk);
	ft_lst_modif_tk_str(*head_tk, del_whitespace);
	// print_lst(*head_tk);
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	// print_lst(*head_tk);
	ft_delete_type_token(head_tk, TOKEN_BLANK);
	// print_lst(*head_tk);
	ft_lst_classify_tk_file(*head_tk);
	// print_lst(*head_tk);
	/*TODO: vérification des règles de grammaire ex: deux operateur à la suite-> pas possible*/
	ft_handle_file_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_arg_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_hd_arg_tk(*head_tk);
	ft_delete_type_token(head_tk, TOKEN_HD_DELIM);
	// print_lst(*head_tk);
	return (0);
}






// TEST Minishell
// < "file entree.txt" wc -l |         ls  -l << 'output de sortie'