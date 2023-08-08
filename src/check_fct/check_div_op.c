/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_div_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:29:22 by thibault          #+#    #+#             */
/*   Updated: 2023/08/08 20:08:02 by thibault         ###   ########.fr       */
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
