/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_group_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:58:01 by thibault          #+#    #+#             */
/*   Updated: 2023/08/08 20:07:12 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Opérateurs de Groupement :
() : Exécute les commandes à l'intérieur dans un sous-shell.
{} : Exécute les commandes à l'intérieur dans le shell actuel.
*/

#include "../minishell.h"

int	is_open_brack(char *line, int i)
{
	if (line[i] == '(')
		return (1);
	return (0);
}

int	is_close_brack(char *line, int i)
{
	if (line[i] == ')')
		return (1);
	return (0);
}

int	is_open_cbrack(char *line, int i)
{
	if (line[i] == '{')
		return (1);
	return (0);
}

int	is_close_cbrack(char *line, int i)
{
	if (line[i] == '}')
		return (1);
	return (0);
}
