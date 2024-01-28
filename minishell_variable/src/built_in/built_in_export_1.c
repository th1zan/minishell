/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:51:44 by thibault          #+#    #+#             */
/*   Updated: 2024/01/27 15:34:35 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export(t_tk *tk)
{
	char	*new_var;

	if (tk->tk_arg == 0)
	{
		env_built_in(tk);
		return (0);
	}
	new_var = concat_args(tk);
	return (handle_new_var(tk->env_struct, new_var));
}

int	handle_new_var(t_env *env, char *new_var)
{
	int	validation_result;

	validation_result = is_valid_env_argument(new_var);
	if (validation_result == -2)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(new_var, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		free(new_var);
		return (1);
	}
	else if (validation_result == 0)
	{
		free(new_var);
		return (0);
	}
	return (update_or_add_env_var(env, new_var));
}

int	update_or_add_env_var(t_env *env_struct, char *new_var)
{
	int		index;
	char	**env;

	env = env_struct->env_main;
	index = find_env_var(env, new_var);
	if (index != -1)
	{
		free(env[index]);
		env[index] = new_var;
	}
	else
	{
		if (!add_new_env_var(env_struct, env, new_var))
			return (0);
	}
	if (ft_strncmp(new_var, "PATH", 4) == 0)
		update_path_tab(env_struct);
	return (0);
}

int	add_new_env_var(t_env *env_struct, char **env, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return (0);
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(env_struct->env_main);
	env_struct->env_main = new_env;
	return (1);
}

void	update_path_tab(t_env *env)
{
	free(env->path_tab);
	env->path_tab = get_path_tab(env->env_main);
}
