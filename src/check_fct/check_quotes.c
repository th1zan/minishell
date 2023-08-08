/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:54:58 by thibault          #+#    #+#             */
/*   Updated: 2023/08/08 20:07:41 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char *line, int i)
{
	int	ctrl;

	ctrl = 0;
	if (is_simple_quote(line, i))
		ctrl++;
	if (is_back_quote(line, i))
		ctrl++;
	if (is_double_quote(line, i))
		ctrl++;
	if (ctrl > 0)
		return (1);
	return (0);
}

int	is_simple_quote(char *line, int i)
{
	if (line[i] == '\'')
		return (1);
	return (0);
}

int	is_back_quote(char *line, int i)
{
	if (line[i] == '`')
		return (1);
	return (0);
}

int	is_double_quote(char *line, int i)
{
	if (line[i] == '"')
		return (1);
	return (0);
}
