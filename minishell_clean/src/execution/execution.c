/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:50:29 by thibault          #+#    #+#             */
/*   Updated: 2023/11/14 11:30:55 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_resources(char **cmd, char ***arg_table)
{
	free(*cmd);
	free_strtab(*arg_table);
	free(*arg_table);
}

int	handle_fork_error(char **cmd, char ***arg_table)
{
	free_resources(cmd, arg_table);
	perror("fork error");
	return (-1);
}

void	exe_child_process(t_env *env, t_tk *tmp, char **cmd, char ***arg_table)
{
	set_fd_for_pipe(tmp);
	close_all_fd(&(env->tk_head));
	if (execve(*cmd, *arg_table, env->env_main) == -1)
	{
		free_resources(cmd, arg_table);
		perror("error when executing the command");
		exit(1);
	}
}

int	execute_non_builtin(t_env *env, t_tk *tmp)
{
	int		pid;
	char	**arg_table;
	char	*cmd;

	arg_table = NULL;
	cmd = NULL;
	cmd_arg_list_to_table(tmp, &arg_table, &cmd);
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(&cmd, &arg_table));
	if (pid == 0)
		exe_child_process(env, tmp, &cmd, &arg_table);
	else
	{
		free(cmd);
		free(arg_table);
		tmp->pid = pid;
	}
	return (0);
}

int	execution(t_env *env, t_tk **tk)
{
	t_tk	*tmp;
	int		status_built_in;
	int		status_bin;
	int		exec_status;

	tmp = *tk;
	status_built_in = 0;
	if (tmp && (tmp->type != TK_CMD && tmp->type != TK_CMD_BUILT_IN))
		tmp = get_next_cmd(tmp);
	while (tmp)
	{
		if (tmp->type == TK_CMD)
			if (execute_non_builtin(env, tmp) == -1)
				return (-1);
		if (tmp->type == TK_CMD_BUILT_IN)
			status_built_in = is_builtin_exec(tmp);
		tmp = get_next_cmd(tmp);
	}
	close_all_fd(tk);
	status_bin = wait_all_pid(tk);
	exec_status = update_status_variable(env, status_bin, status_built_in);
	return (exec_status);
}
