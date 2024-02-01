/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:36:42 by thibault          #+#    #+#             */
/*   Updated: 2024/02/01 20:14:32 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//my attempt to change shlvl in env_init.c file (which is now more than 25lines)
//leaks --atExit -- ./minishell shows no leaks but 
//can you see any potential issues with memory?

char	*find_shlvl(char **env)
{
	int			prefix_len;
	const char	*prefix;

	prefix = "SHLVL=";
	prefix_len = ft_strlen(prefix);
	while (*env)
	{
		if (ft_strncmp(*env, prefix, prefix_len) == 0)
			return (*env + prefix_len);
		env++;
	}
	return (NULL);
}

void	update_shlvl(char ***env)
{
	int		shlvl;
	int		i;
	char	*shlvl_str;
	char	*new_shlvl_str;

	shlvl_str = find_shlvl(*env);
	if (shlvl_str != NULL)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	new_shlvl_str = ft_itoa(shlvl);
	if (!new_shlvl_str)
		return ;
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "SHLVL=", 6) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("SHLVL=", new_shlvl_str);
			break ;
		}
		i++;
	}
	free(new_shlvl_str);
}

/* currently the update of shlvl doesn't work */

// int	add_new_oldshlvl(char *new_shlvl, t_env *env_struct)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	while (env_struct->env_main[i])
// 		i++;
// 	new_env = (char **)malloc((i + 2) * sizeof(char ));
// 	if (!new_env)
// 		return (1);
// 	i = 0;
// 	while (env_struct->env_main[i])
// 	{
// 		new_env[i] = env_struct->env_main[i];
// 		i++;
// 	}
// 	new_env[i] = ft_strjoin("SHLVL=", new_shlvl);
// 	new_env[i + 1] = NULL;
// 	free(env_struct->env_main);
// 	env_struct->env_main = new_env;
// 	return (0);
// }

// int	calculate_new_shlvl(char **env, int incrementation, int index)
// {
// 	int	level;

// 	if (index != -1)
// 		level = atoi(&env[index][6]) + incrementation;
// 	else
// 		level = 1;
// 	return (level);
// }

// int	update_env_shlvl(char *new_shlvl, int index, t_env *env_struct)
// {
// 	char	**env;

// 	env = env_struct->env_main;
// 	if (index != -1)
// 	{
// 		free(env[index]);
// 		env[index] = new_shlvl;
// 	}
// 	else
// 	{
// 		if (add_new_oldshlvl(new_shlvl, env_struct))
// 		{
// 			free(new_shlvl);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// int	update_oldshlvl(int incrementation, t_env *env_struct)
// {
// 	char	**env;
// 	int		index;
// 	int		level;
// 	char	*level_str;
// 	char	*new_shlvl;

// 	env = env_struct->env_main;
// 	index = find_env_var(env, "SHLVL");
// 	level = calculate_new_shlvl(env, incrementation, index);
// 	level_str = ft_itoa(level);
// 	new_shlvl = ft_strjoin("SHLVL=", level_str);
// 	free(level_str);
// 	return (update_env_shlvl(new_shlvl, index, env_struct));
// }

// /* add this func to the end of parse_token func in parse_token.c file */

// int	handle_shlvl(t_tk *tk)
// {
// 	t_tk	*tmp;

// 	if (!tk)
// 		return (1);
// 	tmp = tk;
// 	while (tmp)
// 	{
// 		if (tmp->type == TK_CMD
// 			&& ft_strncmp(tmp->tk_arg->tk_str, "minishell", 9) == 0)
// 		{
// 			if (update_oldshlvl(1, tmp->env_struct) != 0)
// 				return (1);
// 		}
// 		if (tmp->type == TK_CMD_BUILT_IN
// 			&& ft_strncmp(tmp->tk_arg->tk_str, "exit", 4) == 0)
// 		{
// 			if (update_oldshlvl(-1, tmp->env_struct) != 0)
// 				return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
