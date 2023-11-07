/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:31:27 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 09:42:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*concat_args(t_tk *tk)
{
	char	*new_var;
	char	*tmp;

	new_var = ft_strdup("");
	if (!new_var)
		return (NULL);
	while (tk->tk_arg)
	{
		tmp = ft_strjoin(new_var, tk->tk_arg->tk_str);
		free(new_var);
		if (!tmp)
			return (NULL);
		new_var = tmp;
		tk = advance_and_free(tk);
	}
	return (new_var);
}

t_tk	*advance_and_free(t_tk *tk)
{
	t_tk	*next_arg;

	next_arg = tk->tk_arg->next;
	free(tk->tk_arg->tk_str);
	free(tk->tk_arg);
	tk->tk_arg = next_arg;
	return (tk);
}

int	find_env_var(char **env, char *var_name)
{
	int		i;
	int		j;
	char	*tmp_env;

	if (!var_name || !*var_name)
		return (-1);
	i = 0;
	tmp_env = NULL;
	while (env[i] != NULL)
	{
		tmp_env = env[i];
		j = 0;
		while (tmp_env[j] && var_name[j] && tmp_env[j] == var_name[j])
		{
			if (tmp_env[j + 1] && tmp_env[j + 1] == '='
				&& (var_name[j + 1] == 0 || var_name[j + 1] == '='))
			{
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int	is_valid_env_argument(char *arg)
{
	if (!arg || arg[0] == '\0')
		return (-1);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (-2);
	return (validate_env_arg_characters(arg));
}

int	validate_env_arg_characters(char *arg)
{
	int	i;
	int	equals_found;

	i = 1;
	equals_found = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			if (!equals_found && arg[i + 1] == '\0')
				return (1);
			equals_found = 1;
			break ;
		}
		else if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (-2);
		i++;
	}
	if (equals_found)
		return (1);
	return (0);
}
