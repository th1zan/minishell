/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:58:01 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 10:25:18 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir_out(char *line, int i)
{
	if (line[i] == '>' && (line[i + 1] == '\0' || line[i + 1] != '>'))
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
	if (line[i] == '<' && (line[i + 1] == '\0' || line[i + 1] != '<'))
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
	if (line[i] == '|' && (line[i + 1] == '\0' || line[i + 1] != '|'))
		return (1);
	return (0);
}
