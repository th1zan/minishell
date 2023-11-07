/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:31:29 by thibault          #+#    #+#             */
/*   Updated: 2023/11/06 11:32:12 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	del_whitespace(char **str)
{
	int		begin;
	int		end;
	int		len;
	char	*temp;

	if (!*str || **str == '\0')
		return (0);
	begin = 0;
	while (str[begin])
	{
		if (!str[begin])
			break ;
		return (0);
	}
	begin = 0;
	while (is_whitespace((*str)[begin]))
		begin++;
	end = ft_strlen(*str) - 1;
	while (is_whitespace((*str)[end]))
		end--;
	len = end - begin + 1;
	temp = *str;
	*str = ft_substr(temp, begin, len);
	free(temp);
	return (0);
}

char	*get_var_value(char *input, int *i, char **var_values_tab)
{
	char	*var_name;
	char	*var_value_tab;
	char	*var_value;

	var_name = get_var_name_from_input(input, i);
	var_value_tab = find_value_in_tab(var_name, var_values_tab);
	if (var_value_tab)
		var_value = get_value_after_equal(var_value_tab);
	else
		var_value = NULL;
	if (!var_value)
		var_value = ft_strdup("");
	free(var_name);
	return (var_value);
}
