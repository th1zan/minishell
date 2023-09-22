/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:45:21 by thibault          #+#    #+#             */
/*   Updated: 2023/09/18 17:38:50 by thibault         ###   ########.fr       */
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
				printf("File '%s' exist and can be read\n", tk->tk_arg->tk_str);
				return (0);
			} 
			else
			{
				printf("File '%s' DOES NOT exist or cannot be read.\n", tk->tk_arg->tk_str);
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
			if (test_cmd(tk) == 1)
				return (1);
		tk = tk->next;
	}

	return (0);
}

int	test_cmd(t_tk *tk)
{
	char	**path;
	char	*cmd;
	char	*temp;
	int		i;

	// cmd = NULL;
	path = tk->env;
	cmd = tk->tk_str;
	temp = NULL;
	i = 0;
	while (path[i] != 0)
	{
		temp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(temp, tk->tk_str);
		// printf("cmd: %s\n", cmd);
		free(temp);
		if (check_access(cmd) == 1)
		{
			printf("cmd %s exists in the paths\n", tk->tk_str);
			return (0);
		}
		else
		{
			i++;
		}
			
	}
	printf("cmd %s DON'T EXIST in the paths\n", tk->tk_str);
	return (1);
}

int	check_access(char *cmd)
{
	int	get_access;

	get_access = 0;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == -1)
		{
			ft_putstr_fd("pipex: cmd can't be executed by the user: ", 2);
			return (1);
		}
		get_access = 1;
	}
	return (get_access);
}