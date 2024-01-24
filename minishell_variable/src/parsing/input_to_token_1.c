/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:17:58 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_delimiter_quotes(char *input, int *i)
{
	int		start_quote;
	char	tmp_quote;
	int		len;

	len = ft_strlen(input);
	start_quote = *i;
	tmp_quote = input[*i];
	(*i)++;
	while (*i < len)
	{
		if (input[*i] == tmp_quote)
			break ;
		(*i)++;
	}
	if (*i == len)
		*i = start_quote + 1;
}

void	process_character(char *input, int *delimiter, int *i)
{
	int	len;

	len = ft_strlen(input);
	delimiter[*i] = 1;
	if (is_quote(input, *i))
		handle_delimiter_quotes(input, i);
	(*i)++;
	while (*i < len)
	{
		if (is_quote(input, *i))
		{
			handle_delimiter_quotes(input, i);
		}
		if (!ft_isprint(input[*i]) || is_whitespace(input[*i])
			|| input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
			break ;
		(*i)++;
	}
}

void	process_special_delimiters(char *input, int *delim, int *i, int len)
{
	if (input[*i] == '<' || input[*i] == '>')
	{
		delim[*i] = 1;
		(*i)++;
		if (*i < len && input[*i] == input[*i - 1])
			(*i)++;
	}
	else if (input[*i] == '|')
	{
		delim[*i] = 1;
		(*i)++;
	}
}

void	initialize_delimiters(char *input, int *delimiter)
{
	int	i;
	int	len;

	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		if (is_whitespace(input[i]))
		{
			delimiter[i] = 1;
			while (++i < len && is_whitespace(input[i]))
				;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			process_special_delimiters(input, delimiter, &i, len);
		else if (ft_isprint(input[i]) && input[i] != ' ')
			process_character(input, delimiter, &i);
		else
			i++;
	}
}
