/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:50:20 by thibault          #+#    #+#             */
/*   Updated: 2024/01/27 17:26:46 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_arg_list_to_table(t_tk *tk, char ***arg_table, char **cmd)
{
	char	*tmp_str;
	t_tk	*tmp;
	char	*tmp_cmd;

	tmp = tk;
	tk_arg_to_table(tmp, arg_table);
	tmp_cmd = tmp->tk_str;
	if (tmp_cmd[0] == '/')
		*cmd = ft_strdup(tmp_cmd);
	else
	{
		if (get_cmd_path(tmp) == SUCCESS)
		{
			tmp_str = ft_strjoin(tmp->path, "/");
			*cmd = ft_strjoin(tmp_str, tmp->tk_str);
			free(tmp_str);
		}
	}
	return (0);
}

int	tk_arg_to_table(t_tk *tk, char	***arg_table)
{
	t_tk	*tmp;
	int		size_tab;

	tmp = tk->tk_arg;
	size_tab = 1;
	while (tmp)
	{
		size_tab++;
		tmp = tmp->next;
	}
	malloc_strtab(arg_table, size_tab);
	(*arg_table)[0] = tk->tk_str;
	tmp = tk->tk_arg;
	size_tab = 1;
	while (tmp)
	{
		(*arg_table)[size_tab] = tmp->tk_str;
		size_tab++;
		tmp = tmp->next;
	}
	return (0);
}

int	check_and_set_path(t_tk *tk, char *cmd, char *path)
{
	if (check_access(tk->env_struct, cmd) == SUCCESS)
	{
		tk->path = path;
		free(cmd);
		return (SUCCESS);
	}
	free(cmd);
	return (FAILURE);
}

int	get_cmd_path(t_tk *tk)
{
	char	*cmd;
	char	*temp;
	int		i;

	i = 0;
	while (tk->env_struct->path_tab[i])
	{
		temp = ft_strjoin(tk->env_struct->path_tab[i], "/");
		cmd = ft_strjoin(temp, tk->tk_str);
		free(temp);
		if (check_and_set_path(tk, cmd, tk->env_struct->path_tab[i]) == SUCCESS)
			return (0);
		i++;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tk->tk_str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	// printf("get_cmd_path::\n");
	tk->env_struct->status = 127;
	return (1);
}
