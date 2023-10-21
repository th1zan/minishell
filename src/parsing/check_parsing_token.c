/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:45:21 by thibault          #+#    #+#             */
/*   Updated: 2023/10/18 16:37:26 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int		check_input_file(t_tk *tk)
{
	while (tk != NULL)
	{
		if (tk->type == TK_IN_CHEVRON)
		{
			// printf("file:%s\n")
			if (access(tk->tk_arg->tk_str, R_OK) == 0)
			{
				// file exist and can be readed
				// printf("file: %s: exist and can be read\n", tk->tk_arg->tk_str);
				return (0);
			} 
			else
			{
				printf("minishell: %s: parsing: No such file or directory\n", tk->tk_arg->tk_str);
				return (1);
			}
		}
		tk = tk->next;
	}
	return (0);
}

int		check_cmd(t_tk *tk)
{
	while (tk != NULL)
	{
		if (tk->type == TK_CMD)
			if (test_cmd(tk) == FAILURE)
			{
				return (1);
			}
		tk = tk->next;
	}

	return (SUCCESS);
}

int	test_cmd(t_tk *tk)
{
	char	**path_tab;
	char	*cmd;
	char	*temp;
	int		i;

	// cmd = NULL;
	path_tab = global_env->path_tab;
	// printf("TEST CMD, path_tab: %p\n", path_tab);
	// if (path_tab)
	// 	print_strtab(path_tab);
	cmd = tk->tk_str;
	temp = NULL;
	if(cmd[0] == '/')
	{
		if (check_access(cmd) == SUCCESS)
		{
			return (SUCCESS);
		}
	}
	
	if (!path_tab)
	{
		global_env->status = 127;
		printf("minishell: %s: Command not found \n", tk->tk_str);
		return (FAILURE);
	}
	i = 0;
	while (path_tab[i] != 0)
	{
		temp = ft_strjoin(path_tab[i], "/");
		cmd = ft_strjoin(temp, tk->tk_str);
		// printf("cmd: %s\n", cmd);
		free(temp);
		if (check_access(cmd) == SUCCESS)
		{
			free(cmd);
			return (SUCCESS);
		}
		else
		{
			free(cmd);
			i++;
		}
			
	}
	// free(cmd);
	if (global_env->status == 127)
		printf("minishell: %s: Command not found \n", tk->tk_str);
	if (global_env->status == 126)
		printf("minishell: %s: Permission denied\n", tk->tk_str);
	return (FAILURE);
}


int	check_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		global_env->status = 127;
		return (FAILURE);
	}
	else if (access(cmd, X_OK) == -1)
	{
		global_env->status = 126;
		return (FAILURE);
	}
	return (SUCCESS);
}
