/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:29:22 by thibault          #+#    #+#             */
/*   Updated: 2023/08/09 22:22:42 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Opérateurs de Contrôle :

&& : Exécute la commande suivante seulement si la commande précédente réussit.
|| : Exécute la commande suivante seulement si la commande précédente échoue.
; : Exécute la commande précédente, puis la commande suivante.
& : Exécute la commande en arrière-plan.
! : Inverse le code de sortie de la commande (utilisé dans les tests).
*/

int	is_twochar_delim(char *line, int i)
{
	int	ctrl;

	ctrl = 0;
	if (is_double_pipe(line, i))
		ctrl++;
	if (is_double_amp(line, i))
		ctrl++;
	if (is_redir_out_app(line, i))
		ctrl++;
	if (is_redir_err(line, i))
		ctrl++;
	if (is_here_doc(line, i))
		ctrl++;	
	if (ctrl > 0)
		return (1);
	return (0);
}

int	is_onechar_delim(char *line, int i)
{
	int	ctrl;

	ctrl = 0;
	if (is_semicol(line, i))
		ctrl++;
	if (is_amp(line, i))
		ctrl++;
	if (is_excl(line, i))
		ctrl++;
	if (is_redir_out(line, i))
		ctrl++;
	if (is_redir_in(line, i))
		ctrl++;
	if (is_pipe(line, i))
		ctrl++;
	if (ctrl > 0)
		return (1);
	return (0);
}

int	is_ctrl_op(char *line, int i)
{
	int	ctrl;

	ctrl = 0;
	if (is_double_pipe(line, i))
		ctrl++;
	if (is_double_amp(line, i))
		ctrl++;
	if (is_semicol(line, i))
		ctrl++;
	if (is_amp(line, i))
		ctrl++;
	if (is_excl(line, i))
		ctrl++;
	if (ctrl > 0)
		return (1);
	return (0);
}

/*
Opérateurs de Redirection :

>> : Redirige la sortie standard  (ajoute à la fin si le fichier existe).
2> : Redirige la sortie d'erreur vers un fichier.
> : Redirige la sortie standard  (écrase le fichier si existant).
< : Redirige l'entrée standard depuis un fichier.
| : Crée un pipeline. 
(2>&1 : Fusionne la sortie d'erreur avec la sortie standard.)

*/

int	is_redir_op(char *line, int i)
{
	int	ctrl;

	ctrl = 0;
	if (is_redir_out_app(line, i))
		ctrl++;
	if (is_redir_err(line, i))
		ctrl++;	
	if (is_redir_out(line, i))
		ctrl++;
	if (is_redir_in(line, i))
		ctrl++;
	if (is_pipe(line, i))
		ctrl++;
	if (ctrl > 0)
		return (1);
	return (0);
}

int	is_group_op(char *line, int i)
{
	int	ctrl;

	ctrl = 0;
	if (is_open_brack(line, i))
		ctrl++;
	if (is_close_brack(line, i))
		ctrl++;
	if (is_open_cbrack(line, i))
		ctrl++;
	if (is_close_cbrack(line, i))
		ctrl++;
	if (ctrl > 0)
		return (1);
	return (0);
}
