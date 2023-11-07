/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:17:14 by thibault          #+#    #+#             */
/*   Updated: 2023/11/06 12:29:51 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_inside_simple_quote(char *input, int index)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (i < index && input[i])
	{
		if (input[i] == '\'')
		{
			if (in_quote)
				in_quote = 0;
			else
				in_quote = 1;
		}
		i++;
	}
	if (in_quote)
		return (SUCCESS);
	else
		return (FAILURE);
}

char	*replace_var_status_in_string(char *input_str, int *i, char *var_value)
{
	char	*tmp;
	char	*tmp2;
	char	*result;
	int		start;
	int		var_name_len;

	start = *i;
	var_name_len = 2;
	tmp = ft_substr(input_str, 0, start);
	tmp2 = ft_strjoin(tmp, var_value);
	free(tmp);
	result = ft_strjoin(tmp2, &input_str[start + var_name_len]);
	free(tmp2);
	return (result);
}

char	*str_with_valu(char *begin, char *var_value, char *input, int *tab_pos)
{
	char	*tmp;
	char	*final_result;

	tmp = ft_strjoin(begin, var_value);
	if (!tmp)
		return (NULL);
	final_result = ft_strjoin(tmp, input + tab_pos[0] + tab_pos[1]);
	free(tmp);
	return (final_result);
}

char	*replace_var_in_str(char *input_str, int *i, char **env)
{
	char	*var_value;
	char	*begin;
	char	*result;
	int		tab_start_len[2];

	tab_start_len[0] = *i;
	var_value = get_var_value(input_str, i, env);
	if (var_value == NULL)
		var_value = ft_strdup("");
	tab_start_len[1] = get_var_name_len_from_input(input_str, *i);
	begin = ft_substr(input_str, 0, tab_start_len[0]);
	if (begin == NULL)
	{
		free(var_value);
		return (NULL);
	}
	result = str_with_valu(begin, var_value, input_str, tab_start_len);
	free(begin);
	free(var_value);
	return (result);
}
