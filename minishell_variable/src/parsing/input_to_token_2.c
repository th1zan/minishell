/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2024/02/01 14:57:24 by thibault         ###   ########.fr       */
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
	t_tk	*new_tk;

	new_tk = NULL;
	if (len > 0)
	{
		tk_str = ft_substr(input, begin, len);
		if (!tk_str)
			return (-1);
		new_tk = ft_lstnew(tk_str);
		ft_lstadd_back(tk, new_tk);
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

int	put_env_to_token(t_tk *tk, t_env *env)
{
	t_tk	*tmp;

	if (!(tk))
		return (1);
	tmp = tk;
	while (tmp)
	{
		tmp->path_tab = env->path_tab;
		tmp->env = &(env->env_main);
		tmp->env_struct = env;
		tmp = tmp->next;
	}
	return (0);
}
