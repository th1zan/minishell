/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:54:16 by thibault          #+#    #+#             */
/*   Updated: 2023/11/06 11:32:17 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_name_from_input(char *input, int *i)
{
	int		end;

	end = 0;
	(*i)++;
	while (is_portable_filename_char(input[*i + end]) == 1)
		end++;
	return (ft_substr(input, *i, end));
}

int	get_var_name_len_from_input(char *input, int i)
{
	int		len;

	len = 0;
	while (is_portable_filename_char(input[i + len]) == 1)
		len++;
	len++;
	return (len);
}

char	*find_value_in_tab(char *var_name, char **var_values_tab)
{
	int	i;

	i = 0;
	while (var_values_tab[i])
	{
		if (ft_strncmp(var_name, var_values_tab[i], ft_strlen(var_name)) == 0)
			return (var_values_tab[i]);
		i++;
	}
	return (NULL);
}

char	*get_value_after_equal(char *var_value)
{
	int	i;

	i = 0;
	while (var_value && var_value[i] != '=')
		i++;
	i++;
	return (ft_substr(var_value, i, ft_strlen(var_value) - i));
}
