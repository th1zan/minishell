/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:56:39 by thibault          #+#    #+#             */
/*   Updated: 2024/01/27 16:36:29 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_entries(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**copy_env(char **envp, int count)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		new_env[i] = strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
	}
	new_env[count] = NULL;
	return (new_env);
}

t_env	*init_env(char **envp)
{
	t_env	*new_env;
	int		count;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	if (envp == NULL || *envp == NULL)
	{
		ft_putstr_fd("minishell: environment is NULL.\n", 2);
		return (NULL);
	}
	count = count_env_entries(envp);
	new_env = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->env_main = copy_env(envp, count);
	if (!new_env->env_main)
	{
		free(new_env);
		return (NULL);
	}
	new_env->path_tab = get_path_tab(new_env->env_main);
	new_env->minishell_directory = ft_strdup(cwd);
	// new_env->status = 0;
	g_status = 0;
	// printf("init_env:: g_status %d\n", g_status);
	new_env->tk_head = NULL;
	return (new_env);
}

int	parse_input(char *input, t_env *env)
{
	int		*delimiter_tab;

	delimiter_tab = NULL;
	delimiter_tab = get_delimiter(input);
	if (!delimiter_tab)
	{
		env->error_parsing = 1;
		return (1);
	}
	input_to_token(input, &(env->tk_head), delimiter_tab, env);
	free(delimiter_tab);
	if (parse_token(&(env->tk_head), env))
		return (-1);
	return (0);
}

char	**get_path_tab(char **env_main)
{
	char	**path;
	int		i;
	char	*tmp;

	path = NULL;
	i = 0;
	while (env_main && env_main[i] != 0)
	{
		if (ft_strnstr(env_main[i], "PATH=", 5) != 0)
			break ;
		i++;
	}
	if (!env_main[i])
		return (path);
	path = ft_split(env_main[i], ':');
	if (path[0])
	{
		tmp = ft_strtrim(path[0], "PATH=");
		free (path[0]);
		path[0] = tmp;
	}
	return (path);
}
