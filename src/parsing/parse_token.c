/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/10/29 22:36:27 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_tk **head_tk)
{
	// printf("begin of parse token\n");
	// print_lst(*head_tk);
	ft_lst_modif_tk_str(*head_tk, del_whitespace); //this function, iterrates through the list, applying the del_whitespace function to each node. 
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	// printf("after classifiy operator\n");
	// print_lst(*head_tk);
	ft_lst_replace_var(*head_tk, replace_with_values);
	// printf("after ft_lst_replace_var\n");
	// print_lst(*head_tk);
	// handle_quotes(*head_tk); // quotes déjà gérées dans ft_handle_arg_tk(*head_tk);
	// printf("after handle_quotes\n");
	// print_lst(*head_tk);
	ft_delete_type_token(head_tk, TK_BLANK);
	
	ft_lst_classify_tk_unclassified(*head_tk);
	/*TODO: vérification des règles de grammaire ex: deux operateur à la suite-> pas possible*/
	ft_handle_file_tk(*head_tk);
	
	// printf("after handle_files\n");
	// print_lst(*head_tk);
	handle_quotes(*head_tk); // quotes déjà gérées dans ft_handle_arg_tk(*head_tk);
	

	ft_handle_arg_tk(*head_tk);
	ft_handle_built_in(*head_tk);

	if (check_cmd(*head_tk))
		return (-1);
	// printf("before hd\n");
	// print_lst(*head_tk);
	ft_handle_hd_arg_tk(*head_tk);
	// printf("after hd\n");
	// print_lst(*head_tk);
	// ft_delete_type_token(head_tk, TK_HD_DELIM); // no more TK_HD_DELIM -> fct useless
	ft_delete_type_token(head_tk, TK_HD_ARG);
	
	if (check_input_file(*head_tk))
		return (-1);

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
	// if (!check)
	// 	check = check + 2 * check_cmd(tk);
	// fprintf(stderr, "===INFO===: end of check_cmd, check: %d\n", check);
	// if (!check)
	// 	check = check + 3 * check_input_file(tk);
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
			// tmp->tk_str = remove_quotes(tmp->tk_str, '\'');
			// tmp->tk_str = remove_quotes(tmp->tk_str, '"');
			// tmp->tk_str = remove_quotes(tmp->tk_str, '`');
			// printf("tk->tk->str:%s \n", tmp->tk_str);
			tmp->tk_str = remove_quotes(tmp->tk_str);
			if(tmp->tk_arg)
				handle_quotes(tmp->tk_arg);
			// delete_quotes(&(tmp->tk_str));
		// }
		tmp = tmp->next;
	}
	return (0);
}
// TEST Minishell
// < "file entree.txt" wc -l |         ls  -l << 'output de sortie'



static char	*copy_and_skip_quotes(char *str, char quote)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1)); // -2 pour les quotes, +1 pour '\0'
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		if (str[i] != quote)
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

// char	*remove_quotes(char *str)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*final_str;
// 	char	tmp_quote;

// 	i = 0;
// 	final_str = ft_strdup(str); // Dupliquer la chaîne originale pour éviter de la modifier.
// 	if (!final_str)
// 		return (NULL);
// 	while (final_str[i])
// 	{
// 		if (is_quote(final_str, i)) // Supposons que is_quote vérifie si le caractère est une quote.
// 		{
// 			tmp_quote = final_str[i];
// 			while (final_str[++i] && final_str[i] != tmp_quote)
// 			{
// 				if (final_str[i] == tmp_quote)
// 				{
// 					tmp = copy_and_skip_quotes(final_str, tmp_quote);
// 					free(final_str);
// 					final_str = tmp;
// 					break;
// 				}
// 			}
// 			if (!final_str[i]) // Si nous avons atteint la fin sans trouver une quote fermante.
// 				break;
// 		}
// 		i++;
// 	}
// 	return (final_str);
// }

char	*remove_quotes(char *str)
{
	int		i;
	char	*tmp;
	char	*final_str;
	char	tmp_quote;

	i = 0;
	final_str = ft_strdup(str); // Dupliquer la chaîne originale pour éviter de la modifier.
	if (!final_str)
		return (NULL);
	while (final_str[i])
	{
		if (is_quote(final_str, i)) // Si le caractère est une quote.
		{
			tmp_quote = final_str[i]; // Sauvegarder le type de guillemet actuel.
			// Chercher le guillemet de fermeture correspondant.
			while (final_str[++i] && final_str[i] != tmp_quote)
				; // Ignorer les caractères jusqu'à ce que nous trouvions le guillemet de fermeture.

			if (final_str[i] == tmp_quote) // Si nous avons trouvé un guillemet de fermeture.
			{
				// Copier la chaîne en omettant les guillemets ouverts et fermés.
				tmp = copy_and_skip_quotes(final_str, tmp_quote);
				free(final_str);
				final_str = tmp;
				if (!final_str) // Vérifier les erreurs après l'allocation de mémoire.
					return (NULL);
				i = -1; // Réinitialiser l'index pour repasser à travers la nouvelle chaîne.
			}
			else if (!final_str[i]) // Si nous avons atteint la fin sans trouver un guillemet de fermeture.
			{
				break; // Sortir de la boucle, car il n'y a pas de guillemet de fermeture.
			}
		}
		i++; // Passer au caractère suivant si ce n'est pas un guillemet.
	}
	return (final_str);
}


// Fonction pour copier la chaîne en omettant certaines positions.
// char	*copy_without_quotes(char *str, int len, int *quote_positions, int num_quotes)
// {
// 	char	*new_str;
// 	int		i, j, k;

// 	new_str = (char *)malloc(sizeof(char) * (len - num_quotes + 1));
// 	if (!new_str)
// 		return (NULL);

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (i < len)
// 	{
// 		if (k < num_quotes && i == quote_positions[k])
// 			k++;
// 		else
// 			new_str[j++] = str[i];
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }

// // Fonction principale pour supprimer les guillemets de la chaîne.
// char	*remove_quotes(char *str, char quote_char)
// {
// 	int		*quote_positions;
// 	int		i, quote_count, len;
// 	char	*result;

// 	len = 0;
// 	while (str[len]) len++;  // Calculer la longueur de la chaîne

// 	quote_positions = (int *)malloc(sizeof(int) * len);  // Allouer suffisamment d'espace pour toutes les positions
// 	if (!quote_positions)
// 		return (NULL);

// 	i = 0;
// 	quote_count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == quote_char)
// 		{
// 			if (quote_count % 2 == 0)  // guillemet ouvrant
// 			{
// 				quote_positions[quote_count] = i;
// 				quote_count++;
// 			}
// 			else  // guillemet fermant
// 			{
// 				quote_positions[quote_count] = i;
// 				quote_count++;
// 			}
// 		}
// 		i++;
// 	}

// 	if (quote_count % 2 != 0)  // Si le nombre de guillemets n'est pas pair, ignorer le dernier
// 		quote_count--;

// 	result = copy_without_quotes(str, len, quote_positions, quote_count);
// 	free(quote_positions);
// 	free(str);
// 	return (result);
// }
