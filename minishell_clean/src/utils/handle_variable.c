/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:50:20 by thibault          #+#    #+#             */
/*   Updated: 2023/11/09 16:09:22 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_input_if_needed(char **input, char *new_input)
{
	int	is_updated;

	is_updated = 0;
	if (*input != new_input)
	{
		free(*input);
		*input = new_input;
		is_updated = 1;
	}
	return (is_updated);
}

char	*handle_status_variable(char *input, int *i)
{
	char	*status;
	char	*new_input;

	status = ft_itoa(g_env->status);
	new_input = replace_var_status_in_string(input, i, status);
	(*i) += 1;
	free(status);
	return (new_input);
}

char	*process_variable_replacement(char *input, int *i, char **var_val_tab)
{
	char	*new_input;

	new_input = NULL;
	if (ft_strncmp(&input[*i], "$?", 2) == 0)
		new_input = handle_status_variable(input, i);
	else if (input[*i + 1] == ' ' || input[*i + 1] == '\0'
		|| !ft_isalnum(input[*i + 1]))
		(*i)++;
	else
		new_input = replace_var_in_str(input, i, var_val_tab);
	return (new_input);
}

void	process_input(char **input, int *i, char **var_val_tab, int *is_var)
{
	char	*new_input;

	if ((*input)[*i] == '$' && check_inside_simple_quote(*input, *i) != SUCCESS)
	{
		new_input = process_variable_replacement(*input, i, var_val_tab);
		if (new_input)
			*is_var = update_input_if_needed(input, new_input);
		else
			(*i)--;
	}
	else
		(*i)++;
}

int	replace_with_values(char **input, char ***var_val_tab)
{
	int	i;
	int	is_var;

	is_var = 0;
	i = 0;
	while ((*input)[i])
	{
		process_input(input, &i, *var_val_tab, &is_var);
		i++;
	}
	return (is_var);
}
