/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 21:12:37 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*get_delimiter(char *input)
{
	int	*delimiter;
	int	len;

	len = ft_strlen(input);
	delimiter = (int *)ft_calloc(len + 1, sizeof(int));
	if (!delimiter)
		return (NULL);
	initialize_delimiters(input, delimiter);
	return (delimiter);
}

int	add_token(char *input, int begin, int len, t_tk **tk)
{
	char	*tk_str;

	if (len > 0)
	{
		tk_str = ft_substr(input, begin, len);
		if (!tk_str)
			return (-1);
		ft_lstadd_back(tk, ft_lstnew(tk_str));
	}
	return (0);
}

int	input_to_token(char *input, t_tk **tk, int *delimiter)
{
	int	begin;
	int	i;

	*tk = NULL;
	begin = 0;
	i = 0;
	while (input[i])
	{
		if (delimiter[i])
		{
			if (add_token(input, begin, i - begin, tk) == -1)
				return (-1);
			begin = i;
		}
		i++;
	}
	if (add_token(input, begin, i - begin, tk) == -1)
		return (-1);
	return (0);
}
