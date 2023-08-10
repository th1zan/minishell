/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_div_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:29:22 by thibault          #+#    #+#             */
/*   Updated: 2023/08/09 17:24:28 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Opérateurs Divers :
# : Commence un commentaire.
$ : Utilisé pour accéder à la valeur d'une variable
*, ? : Jokers utilisés 
*/

#include "../minishell.h"

int	is_hashtag(char *line, int i)
{
	if (line[i] == '#')
		return (1);
	return (0);
}

int	is_dollar(char *line, int i)
{
	if (line[i] == '$')
		return (1);
	return (0);
}

int	is_inter_mark(char *line, int i)
{
	if (line[i] == '?')
		return (1);
	return (0);
}

int	is_here_doc(char *line, int i)
{
	if (line[i + 1] == '\0')
		return (0);
	if (line[i] == '<' && line[i + 1] == '<' )
		return (1);
	return (0);
}

int	iswhitespace(int c)
{
	if (c == '\t' || c == '\v' || c == '\n' || c == ' ' || c == '\r' || c == '\f')
		return (1);
	else
		return (0);
}
