/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:58:01 by thibault          #+#    #+#             */
/*   Updated: 2023/08/08 19:41:53 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Opérateurs de Redirection :
> : Redirige la sortie standard  (écrase le fichier si existant).
>> : Redirige la sortie standard  (ajoute à la fin si le fichier existe).
< : Redirige l'entrée standard depuis un fichier.
2> : Redirige la sortie d'erreur vers un fichier.
2>&1 : Fusionne la sortie d'erreur avec la sortie standard.
| : Crée un pipeline. 
*/

#include "../minishell.h"

int	is_redir_out(char *line, int i)
{
	if (line[i] == '<')
		return (1);
	return (0);
}

int	is_redir_out_app(char *line, int i)
{
	if (line[i + 1] == '\0')
		return (0);
	if (line[i] == '>' && line[i + 1] == '>' )
		return (1);
	return (0);
}

int	is_redir_in(char *line, int i)
{
	if (line[i] == '<')
		return (1);
	return (0);
}

int	is_redir_err(char *line, int i)
{
	if (line[i + 1] == '\0')
		return (0);
	if (line[i] == '2' && line[i + 1] == '>' )
		return (1);
	return (0);
}

int	is_pipe(char *line, int i)
{
	if (line[i] == '|')
		return (1);
	return (0);
}
