/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:11:53 by mlachat           #+#    #+#             */
/*   Updated: 2023/09/22 11:49:31 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



/*
1) récupérer la cmd1
2) fork()
3) le child, pid = 0 doit exécuter la commande avec execve (cdm1, arg1)
4) le parent, pid > 0 execute la suite du processus
5) stocker le pid du process parent de la cmd1
6) boucler avec les cmd2 et cmd3
7) attendre la fin des processus: wait(pid_cmd1), wait(pid_cmd2, etc)
*/

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
	// printf("arg_table size:%d\n",size_tab);

	malloc_strtab(arg_table, size_tab);
	(*arg_table)[0] = tk->tk_str;
	// printf("arg_table[0] %s\n", (*arg_table)[0]);
	tmp = tk->tk_arg;

	size_tab = 1;
	while(tmp)
	{
		// printf("tmp->tk_str: %p, %s\n", tmp->tk_str, tmp->tk_str);
		(*arg_table)[size_tab] = tmp->tk_str;
		// printf("arg_table[%d]: %p, %s \n", size_tab, (*arg_table)[size_tab], (*arg_table)[size_tab]);
		
		size_tab++;
		tmp = tmp->next;
	}
	
	// print_strtab(*arg_table);
	// free_strtab(*arg_table);
	return (0);
}


/*for each tk CMD:
			if tk_prev is:
				NULL:
					nothing
				PIPE:
					dup2(pipe_out, stdin)
					close pipe_in
					close pipe_out
				OPERATOR < infile:
					fdin = open(infile)
					dup2(fdin, stdin)
					close fdin

			if tk_next is:
				NULL:
					nothing
				PIPE:
					dup2(pipe_in, stdout)
					close pipe_in
					close pipe_out
				OPERATOR > outfile:
					fdout = open(outfile)
					dup2(fdout, stdout)
					close fdout

			pid = fork()
			if pid == 0:
				execve(cmd)
			else:
				save_pid(pid)

		wait_all_saved_pid
		close_all_pipes

		*/

	// ls -l | wc -l
	// < infile ls -l | wc -l > outfile

int	execution(t_tk **tk)
{
	t_tk	*tmp;
	char	**arg_table;
	int		pid;
	char	*cmd;
	char	*tmp_str;
	
	tmp = *tk;
	if (tmp->type != TK_CMD)
		tmp = get_next_type_tk(tmp, TK_CMD);
	// fprintf(stderr,"tmp %p\n", tmp);
	while(tmp)
	{
		// Get cmd arg as a table (and not as a chained list)
		tk_arg_to_table(tmp, &arg_table);
		get_cmd_path(tmp);
		tmp_str = ft_strjoin(tmp->path, "/");
		cmd = ft_strjoin(tmp_str, tmp->tk_str); //gestion de la mémire à faire
		free(tmp_str);

		
		
		// DEBUG
			fprintf(stderr, "-----------CMD: %s\n", tmp->tk_str);
			// print_lst(*tk);
		
		pid = fork();
		if (pid == -1)
			perror("fork error");

		if (pid == 0)
		{
		
			set_fd_for_cmd(tmp);

			//  if (isatty(STDIN_FILENO)) {
			// printf("stdin (fd %d) is connected to a terminal\n", STDIN_FILENO);
			// } else {
			// printf("stdin (fd %d) is redirected\n", STDIN_FILENO);
			// }

			// if (isatty(STDOUT_FILENO)) {
			// printf("stdout (fd %d) is connected to a terminal\n", STDOUT_FILENO);
			// } else {
			// printf("stdout (fd %d) is redirected\n", STDOUT_FILENO);
			// }


			close_all_fd(tk);
			print_lst(*tk);

						// if (isatty(STDIN_FILENO)) {
						// printf("stdin (fd %d) is connected to a terminal\n", STDIN_FILENO);
						// } else {
						// printf("stdin (fd %d) is redirected\n", STDIN_FILENO);
						// }

						// if (isatty(STDOUT_FILENO)) {
						// printf("stdout (fd %d) is connected to a terminal\n", STDOUT_FILENO);
						// } else {
						// printf("stdout (fd %d) is redirected\n", STDOUT_FILENO);
						// }


			if (execve(cmd, arg_table, tmp->env) == -1)
			{
				perror("error when executing the command");
			}
			// print_lst(*tk);
			exit(1);
		}
		else
		{
			tmp->pid = pid;
		}
		tmp = get_next_type_tk(tmp, TK_CMD);
		// fprintf(stderr, "next TK : TMP : %s\n", tmp->tk_str);
	}
	
	close_all_fd(tk);
	wait_all_pid(tk);
	
	
		// if (isatty(STDIN_FILENO)) {
			// printf("stdin (fd %d) is connected to a terminal\n", STDIN_FILENO);
			// } else {
			// printf("stdin (fd %d) is redirected\n", STDIN_FILENO);
			// }

			// if (isatty(STDOUT_FILENO)) {
			// printf("stdout (fd %d) is connected to a terminal\n", STDOUT_FILENO);
			// } else {
			// printf("stdout (fd %d) is redirected\n", STDOUT_FILENO);
			// }

	print_lst(*tk);
	return (0);
}

int	cmd_fd_is_standard(t_tk *tk)
{
	if (fd_is_standard(tk->fd_in) && fd_is_standard(tk->fd_out))
		return (1);
	return (0);
}

int	fd_is_standard(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return (1);
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

int	get_cmd_path(t_tk *tk)
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
			// printf("path[i] %s added to CMD_TK: %s\n", path[i], tk->tk_str);
			tk->path = path[i];
			return (0);
		}
		else
		{
			i++;
		}
			
	}
	printf("SHOULD NOT HAPPEN --- cmd %s DON'T EXIST in the paths\n", tk->tk_str);
	return (1);
}

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
