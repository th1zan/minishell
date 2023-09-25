/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:11:53 by mlachat           #+#    #+#             */
/*   Updated: 2023/09/25 11:25:40 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	execution(t_tk **tk)
{
	t_tk	*tmp;
	int		pid;
	char	**arg_table;
	char	*cmd;
	
	tmp = *tk;
	arg_table = NULL;
	cmd = NULL;
	if (tmp->type != TK_CMD && tmp->type != TK_CMD_BUILT_IN)
		tmp = get_next_cmd(tmp);
	while(tmp)
	{
		if (tmp->type == TK_CMD)
		{
			arg_table = NULL;
			cmd = NULL;
			cmd_arg_list_to_table(tmp, &arg_table, &cmd);
			
			// fprintf(stderr, "-----------CMD: %s\n", tmp->tk_str);
			
			pid = fork();
			if (pid == -1)
				perror("fork error");
			if (pid == 0)
			{
				set_fd_for_cmd(tmp);
				close_all_fd(tk);
				if (execve(cmd, arg_table, tmp->env) == -1)
				{
					//si execve s'execute, la mémoire sera libérée automatiquement à la fin du process
					// sinon il faut la libérer ci-dessous
					free(cmd);
					free_strtab(arg_table);
					perror("error when executing the command");
					exit(1);
				}
			}
			else
				tmp->pid = pid;
		}
		else if (tmp->type == TK_CMD_BUILT_IN)
		{
				set_fd_for_cmd(tmp);
				is_builtin_exec(tmp);
		}

		tmp = get_next_cmd(tmp);
	}
	
	close_all_fd(tk);
	wait_all_pid(tk);
	return (0);
}


t_tk	*get_next_cmd(t_tk *tk)
{
	t_tk	*tmp;

	if (tk->next)
		tmp = tk->next;
	else
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_tk	*get_next_type_tk(t_tk *tk, int type)
{
	t_tk	*tmp;

	if (tk->next)
		tmp = tk->next;
	else
		return (NULL);
	while (tmp != NULL)
	{
		if (tmp->type == type)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	cmd_arg_list_to_table(t_tk *tk, char ***arg_table, char **cmd)
{
	char	*tmp_str;
	t_tk	*tmp;

	tmp = tk;
	tk_arg_to_table(tmp, arg_table);
	get_cmd_path(tmp);
	tmp_str = ft_strjoin(tmp->path, "/");
	*cmd = ft_strjoin(tmp_str, tmp->tk_str);
	free(tmp_str);
	return(0);
}


int	tk_arg_to_table(t_tk *tk, char	***arg_table)
{
	t_tk	*tmp;
	int		size_tab;

	tmp = tk->tk_arg;
	size_tab = 1;
	while(tmp)
	{
		size_tab++;
		tmp = tmp->next;
	}
	malloc_strtab(arg_table, size_tab);
	(*arg_table)[0] = tk->tk_str;
	tmp = tk->tk_arg;
	size_tab = 1;
	while(tmp)
	{
		(*arg_table)[size_tab] = tmp->tk_str;
		size_tab++;
		tmp = tmp->next;
	}
	// print_strtab(*arg_table);
	return (0);
}


int	get_cmd_path(t_tk *tk)
{
	char	**path;
	char	*cmd;
	char	*temp;
	int		i;

	path = tk->env;
	cmd = tk->tk_str;
	temp = NULL;
	i = 0;
	while (path[i] != 0)
	{
		temp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(temp, tk->tk_str);
		free(temp);
		if (check_access(cmd) == 1)
		{
			// printf("path[i] %s added to CMD_TK: %s\n", path[i], tk->tk_str);
			tk->path = path[i];
			return (0);
		}
		else
			i++;
	}
	fprintf(stderr,"error fct:: get_cmd_path : cmd %s DON'T EXIST in the paths\n", tk->tk_str);
	return (1);
}


int	set_fd_for_cmd(t_tk *tk)
{
	int	fd_in;
	int	fd_out;

	fd_in = tk->fd_in;
	fd_out = tk->fd_out;
	if (tk->prev && tk->prev->type == TK_PIPE)
	{
		if (fd_is_standard(fd_in) == 0)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
			{
				perror("dup2 error: fd_in in set_fd_for_cmd");
				fprintf(stderr, "set_fd_for_cmd :: fd_in: %d, errno: %d\n", fd_in, errno);
				return (-1);
			}
			// fprintf(stderr, "set_fd_for_cmd :: fd_in dup2 %d : %d\n", fd_in, STDIN_FILENO);
		}
	}
	if (tk->next && tk->next->type == TK_PIPE)
	{
		if (fd_is_standard(fd_out) == 0)
		{
			
			if (dup2(fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2 error: fd_out in set_fd_for_cmd");
				fprintf(stderr, "set_fd_for_cmd :: fd_out: %d, errno: %d\n", fd_out, errno);
				return (-1);
			}
		}
			// fprintf(stderr, "set_fd_for_cmd :: fd_out dup2 %d : %d\n", fd_out, STDOUT_FILENO);
	}
	return (0);
}

int	fd_is_standard(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return (1);
	return (0);
}


int	close_all_fd(t_tk **tk)
{
	t_tk	*tmp;
	int		ret;// Variable pour stocker le retour de close

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD)
		{
			if ((tmp->fd_in != -1) && (fd_is_standard(tmp->fd_in) != 1))
			{
				ret = close(tmp->fd_in);
				if (ret == -1) {
					perror("Error closing fd_in");
				}
				// fprintf(stderr, "close_all_fd :: close : %d\n", tmp->fd_in);
				tmp->fd_in = -1;
			}
			if ((tmp->fd_out != -1) && (fd_is_standard(tmp->fd_out) != 1))
			{
				ret = close(tmp->fd_out);
				if (ret == -1) {
					perror("Error closing fd_out");
				}
				// fprintf(stderr, "close_all_fd :: close : %d\n", tmp->fd_out);
				tmp->fd_out = -1;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	wait_all_pid(t_tk **tk)
{
	t_tk	*tmp;
	int		status;

	tmp = *tk;
	if (tmp->type != TK_CMD)
		tmp = get_next_type_tk(tmp, TK_CMD);
	status = 0;
	while(tmp)
	{
		
		waitpid(tmp->pid, &status, 0);
		tmp = get_next_type_tk(tmp, TK_CMD);
	}
	return (status);
}

/*
TO DELETE

char	*arg_to_str(t_tk *tk)
{
	char	*arg;
	char	*temp;

	if (!tk) return NULL;

	arg = ft_strdup(tk->tk_str);
	while(tk)
	{
		temp = ft_strjoin(arg, " ");
		free(arg);
		arg = ft_strjoin(temp, tk->tk_str);
		free(temp);

		tk = tk->next;
	}

	return (arg);
}
*/