/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:50:20 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 22:50:07 by zsoltani         ###   ########.fr       */
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

char	*handle_status_variable(char *input, int *i, t_env *env)
{
	char	*status;
	char	*new_input;

	(void)env;
	status = ft_itoa(g_status);
	new_input = replace_var_status_in_string(input, i, status);
	(*i) += 1;
	free(status);
	return (new_input);
}

char	*expand_var(char *input, int *i, char **var_val_tab, t_env *env)
{
	char	*new_input;

	new_input = NULL;
	if (ft_strncmp(&input[*i], "$?", 2) == 0)
		new_input = handle_status_variable(input, i, env);
	else if (input[*i + 1] == ' ' || input[*i + 1] == '\0'
		|| !ft_isalnum(input[*i + 1]))
		(*i)++;
	else
		new_input = replace_var_in_str(input, i, var_val_tab);
	return (new_input);
}

void	process_input(char **input, int *i, t_tk *tk, int *is_var)
{
	char	*new_input;
	char	**var_val_tab;
	t_env	*env;

	var_val_tab = *(tk->env);
	env = tk->env_struct;
	if ((*input)[*i] == '$' && check_inside_simple_quote(*input, *i) != SUCCESS)
	{
		new_input = expand_var(*input, i, var_val_tab, env);
		if (new_input)
			*is_var = update_input_if_needed(input, new_input);
		else
			(*i)--;
	}
}

int	replace_with_values(char **input, t_tk *tk)
{
	int	i;
	int	is_var;

	is_var = 0;
	i = 0;
	while ((*input)[i])
	{
		process_input(input, &i, tk, &is_var);
		i++;
	}
	return (is_var);
}
