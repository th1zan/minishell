/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/08/16 09:58:31 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
		Analyser la liste
		1. Input
			-> operator
			-> token
		2. Classify operator
		4. Classifiy token
			-> If token contains quote
				-> Quoted token
				-> other token
		5. Analyse quoted token
			-> single quote token
			-> double quote token
		6. Handle single quote token
		7. Handle double quote token
		8. Handle newline token
		9. Handle blank token
		10. Handle word token


*/

	int	parse_token(t_tk **head_tk)
{
	// char *str = ft_strdup("   Coucou   _   ");
	
	
	// del_whitespace(&str);
	// free(str);

	print_lst(*head_tk);
	ft_lst_modif_tk_str(*head_tk, del_whitespace);
	print_lst(*head_tk);
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	print_lst(*head_tk);
	return (0);
}

int	del_whitespace(char **str)
{
	int		begin;
	int		end;
	int		len;
	char	*temp;

	if (!*str || **str == '\0')
		return (0);
	begin = 0;
	while(str[begin])
	{
		if (!str[begin])
			break;
		return(0);
	}
	begin = 0;
	while (is_whitespace((*str)[begin]))
		begin++;
	end = ft_strlen(*str) -1;
	while(is_whitespace((*str)[end]))
		end--;
	len = end - begin + 1;
	temp = *str;
	*str = ft_substr(temp, begin, len);
	free(temp);

	printf("str: %s\n", *str);
	return (0);
}

// int	del_whitespace(char **str)
// {
// 	int		begin;
// 	int		end;
// 	int		len;
// 	char	*temp;

// 	if (!*str || **str == '\0') // Vérifie si la chaîne est NULL ou vide
// 		return (0);

// 	begin = 0;
// 	while (is_whitespace((*str)[begin]))
// 		begin++;

// 	end = ft_strlen(*str) - 1;
// 	while (end >= 0 && is_whitespace((*str)[end])) // Ajoute une vérification pour s'assurer que end ne devient pas négatif
// 		end--;

// 	// Si la chaîne est entièrement composée d'espaces blancs
// 	if (end < begin)
// 	{
// 		free(*str);
// 		*str = ft_strdup(""); // Remplace la chaîne par une chaîne vide
// 		return (0);
// 	}

// 	len = end - begin + 1;
// 	temp = *str;
// 	*str = ft_substr(temp, begin, len);
// 	free(temp);

// 	printf("str: %s\n", *str);
// 	return (0);
// }


/*Redirection
	TOKEN_REDIRECTION = 10,
	TOKEN_PIPE,
	TOKEN_INPUT_CHEVRON,
	TOKEN_OUTPUT_CHEVRON,
	TOKEN_APPEND_CHEVRON,
	TOKEN_HERE_DOC,
	*/

int	classify_operator(char *str)
{
	if (!str || ft_strlen(str) > 2)
		return (TOKEN_UNCLASSIFIED);
	if (*str == '\0')
		return (TOKEN_BLANK);
	if(is_here_doc(str, 0))
		return(TOKEN_HERE_DOC);
	if(is_redir_out_app(str, 0))
		return(TOKEN_APPEND_CHEVRON);
	if(is_redir_in(str, 0))
		return(TOKEN_INPUT_CHEVRON);
	if(is_redir_out(str, 0))
		return(TOKEN_OUTPUT_CHEVRON);
	if(is_pipe(str, 0))
		return(TOKEN_PIPE);
	return (TOKEN_UNCLASSIFIED);
}