/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:13:19 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_and_skip_quotes(char *str, char quote)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
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

int	remove_quotes_loop(char **final_str, int *i)
{
	char	tmp_quote;
	char	*tmp;

	if (is_quote(*final_str, *i))
	{
		tmp_quote = (*final_str)[*i];
		while ((*final_str)[++(*i)] && (*final_str)[*i] != tmp_quote)
			;
		if ((*final_str)[*i] == tmp_quote)
		{
			tmp = copy_and_skip_quotes(*final_str, tmp_quote);
			free(*final_str);
			*final_str = tmp;
			if (!*final_str)
				return (0);
			*i = -1;
		}
	}
	return (1);
}

char	*remove_quotes(char *str)
{
	int		i;
	char	*final_str;

	i = 0;
	final_str = ft_strdup(str);
	if (!final_str)
		return (NULL);
	while (final_str[i])
	{
		if (remove_quotes_loop(&final_str, &i) == 0)
			break ;
		i++;
	}
	return (final_str);
}
