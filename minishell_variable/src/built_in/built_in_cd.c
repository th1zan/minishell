/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:01:21 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 10:12:00 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_new_oldpwd(char *current_directory)
{
	char	**new_env;
	int		i;

	i = 0;
	while (g_env->env_main[i])
		i++;
	new_env = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return (1);
	i = 0;
	while (g_env->env_main[i])
	{
		new_env[i] = g_env->env_main[i];
		i++;
	}
	new_env[i] = ft_strjoin("OLDPWD=", current_directory);
	new_env[i + 1] = NULL;
	free(g_env->env_main);
	g_env->env_main = new_env;
	return (0);
}

int	update_oldpwd(char *current_directory)
{
	char	**env;
	int		index;

	env = g_env->env_main;
	index = find_env_var(env, "OLDPWD");
	if (index != -1)
	{
		free(env[index]);
		env[index] = ft_strjoin("OLDPWD=", current_directory);
	}
	else
	{
		if (add_new_oldpwd(current_directory))
			return (1);
	}
	return (0);
}

int	cd(t_tk *tk)
{
	char	*path;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	update_oldpwd(cwd);
	if (tk == NULL)
	{
		return (1);
	}
	if (tk->tk_arg == NULL || tk->tk_arg->tk_str == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else
		path = tk->tk_arg->tk_str;
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd:", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": parsing path: No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
