/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ctrl_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfinocie <vfinocie@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:58:01 by thibault          #+#    #+#             */
/*   Updated: 2023/09/16 13:03:27 by vfinocie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Opérateurs de Contrôle :
; : Exécute la commande précédente, puis la commande suivante.
& : Exécute la commande en arrière-plan.
&& : Exécute la commande suivante seulement si la commande précédente réussit.
|| : Exécute la commande suivante seulement si la commande précédente échoue.
! : Inverse le code de sortie de la commande (utilisé dans les tests).
*/

#include "../minishell.h"

int	is_semicol(char *line, int i)
{
	// semicolon is ; I think
	if (line[i] == ',')
		return (1);
	return (0);
}

int	is_amp(char *line, int i)
{
	if (line[i] == '&' && (line[i + 1] == '\0' || line[i + 1] != '&')) //line[i + 1] != '&' I think is already checked in is_double_amp, if it was true then, it won't be checked here, and if it was wrong then, it will be wrong now.
			return (1);
	return (0);
}

int	is_double_amp(char *line, int i)
{
	if (line[i + 1] == '\0')
		return (0);
	if (line[i] == '&' && line[i + 1] == '&' )
		return (1);
	return (0);
}

int	is_excl(char *line, int i)
{
	if (line[i] == '!')
		return (1);
	return (0);
}

int	is_double_pipe(char *line, int i)
{
	if (line[i + 1] == '\0')
		return (0);
	if (line[i] == '|' && line[i + 1] == '|' )
		return (1);
	return (0);
}
