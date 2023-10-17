/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/10/17 11:20:56 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_tk **head_tk)
{
	ft_lst_modif_tk_str(*head_tk, del_whitespace); //this function, iterrates through the list, applying the del_whitespace function to each node. 
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	// printf("after classifiy operator\n");
	// print_lst(*head_tk);
	ft_lst_replace_var(*head_tk, replace_with_values);
	// printf("after ft_lst_replace_var\n");
	// print_lst(*head_tk);
	ft_delete_type_token(head_tk, TK_BLANK);
	ft_lst_classify_tk_unclassified(*head_tk);
	/*TODO: vérification des règles de grammaire ex: deux operateur à la suite-> pas possible*/
	ft_handle_file_tk(*head_tk);
	// printf("after handle_files\n");
	// print_lst(*head_tk);
	// handle_quotes(*head_tk); // quotes déjà gérées dans ft_handle_arg_tk(*head_tk);
	
	ft_handle_arg_tk(*head_tk);
	// printf("before hd\n");
	// print_lst(*head_tk);
	ft_handle_hd_arg_tk(*head_tk);
	// printf("after hd\n");
	// print_lst(*head_tk);
	// ft_delete_type_token(head_tk, TK_HD_DELIM); // no more TK_HD_DELIM -> fct useless
	ft_delete_type_token(head_tk, TK_HD_ARG);
	ft_handle_built_in(*head_tk);

	// printf("after ft_handle_built_in\n");
	// print_lst(*head_tk);
	return (0);
}

int		check_parsing(t_tk *tk)
{
	int	check;

	check = 0;
	check = check_grammar(tk);
	// fprintf(stderr, "===INFO===: end of check_grammar, check: %d\n", check);
	check = check + 2 * check_cmd(tk);
	// fprintf(stderr, "===INFO===: end of check_cmd, check: %d\n", check);
	check = check + 3 * check_input_file(tk);
	// fprintf(stderr, "===INFO===: end of check_input_file, check: %d\n", check);
	if (check > 0)
	{	
		global_env->error_parsing = check;
		return (check);
	}	
	//DEBUG
	// fprintf(stderr, "===INFO===: end of parsing check\n");
	return (0);
}

int	delete_quotes(char **str)
{
	int		len;
	char	*tmp_str;

	len = ft_strlen(*str);
	if (is_double_quote(*str, 0) && is_double_quote(*str, len - 1))
	{
		tmp_str = ft_substr(*str, 1, len - 2);
		free(*str);
		*str = tmp_str;
		return (0);
	}
	else if (is_simple_quote(*str, 0) && is_simple_quote(*str, len - 1))
	{
		tmp_str = ft_substr(*str, 1, len - 2);
		free(*str);
		*str = tmp_str;
		return (0);
	}
	else if (is_back_quote(*str, 0) && is_back_quote(*str, len - 1))
	{
		tmp_str = ft_substr(*str, 1, len - 2);
		free(*str);
		*str = tmp_str;
		return (0);
	}
	return (0);
}


int 	handle_quotes(t_tk *head_tk)
{
	t_tk	*tmp;

	// printf("DEBUG\n");
	tmp = head_tk;
	while (tmp)
	{
		// printf("tk_type %d\n", tmp->type);
		// if (tmp->type == TK_ARG)
		// {
			// printf("tk_str %s\n", tmp->tk_str);
			delete_quotes(&(tmp->tk_str));
		// }
		tmp = tmp->next;
	}
	return (0);
}
// TEST Minishell
// < "file entree.txt" wc -l |         ls  -l << 'output de sortie'