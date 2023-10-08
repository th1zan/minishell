/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:11:53 by mlachat           #+#    #+#             */
/*   Updated: 2023/10/08 23:49:53 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	execution(t_env *env, t_tk **tk)
{
	t_tk	*tmp;
	int		pid;
	char	**arg_table;
	char	*cmd;
	int		status_built_in;
	int		status_bin;
	
	tmp = *tk;
	arg_table = NULL;
	cmd = NULL;
	status_built_in = 0;
	status_bin = 0;
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
				if (execve(cmd, arg_table, tmp->path_tab) == -1)
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
				status_built_in = is_builtin_exec(tmp);
		}

		tmp = get_next_cmd(tmp);
	}
	
	close_all_fd(tk);
	status_bin = wait_all_pid(tk);
	
	update_status_variable(env, status_bin, status_built_in);
	save_status_var_in_env(env);



	

	//DEBUG
		fprintf(stderr, "===INFO===: end of execution\n");
		
		// print_lst(tk_head);
	return (0);
}

// int	save_status_var_in_env(t_env *env_tk)
// {
// 	char	**env;
// 	char	*new_var;
// 	int		index;
// 	int		i;
// 	char	**new_env;

// 	env = env_tk->env_main;
	
// 	new_var = ft_strjoin("?=",ft_itoa(env_tk->status));
// 	printf("save_status_var_in_env:: $? = %s\n", new_var);
// 	index = find_env_var(env, new_var);
// 	// printf("existe index: %d\n", index);

// 	// 4) Si existe alors change la string dans le tableau et libère l'ancienne
// 	if (index != -1)
// 	{
// 		free(env[index]); // libère l'ancienne string
// 		env[index] = new_var; // remplace par la nouvelle string
// 	}
// 	else
// 	{
// 		// 5) Si non, dimensionne nouveau tableau et ajoute une ligne pour la nouvelle variable
// 		i = 0;
// 		while (env[i] != NULL)
// 			i++;

// 		new_env = malloc((i + 2) * sizeof(char*)); // +1 pour la nouvelle variable et +1 pour NULL
		
// 		for (int j = 0; j < i; j++)
// 		{
// 			new_env[j] = env[j];
// 		}
// 		new_env[i] = new_var; // ajoute la nouvelle variable
// 		new_env[i + 1] = NULL;  // termine le tableau avec NULL

// 		// free(env); // libère l'ancien tableau
// 		env_tk->env_main = new_env; // met à jour le pointeur env pour pointer vers le nouveau tableau
// 	}

// 	return (0);

	
// }

int	save_status_var_in_env(t_env *env_tk)
{
	char	**env;
	char	*new_var;
	int		index;
	int		i;
	char	**new_env;

	env = env_tk->env_main;
	
	new_var = ft_strjoin("?=",ft_itoa(env_tk->status));
	printf("save_status_var_in_env:: $? = %s\n", new_var);
	index = find_env_var(env, new_var);

	// Si la variable existe déjà, libérez l'ancienne valeur et mettez à jour avec la nouvelle
	if (index != -1)
	{
		free(env[index]);
		env[index] = new_var;
	}
	else
	{
		i = 0;
		while (env[i] != NULL)
			i++;

		new_env = malloc((i + 2) * sizeof(char*)); // +1 pour la nouvelle variable et +1 pour NULL

		// Insérez la nouvelle variable au début
		new_env[0] = new_var;

		// Copiez les anciennes variables après la nouvelle
		int j = 0;
		while (j < i)
		{
			new_env[j + 1] = env[j];
			j++;
		}
		new_env[i + 1] = NULL;  // termine le tableau avec NULL

		// free(env); // libère l'ancien tableau
		env_tk->env_main = new_env; // met à jour le pointeur env pour pointer vers le nouveau tableau
	}

	return (0);
}


int	update_status_variable(t_env *env, int bin_status, int status_built_in)
{
	if (status_built_in != 0)
	{
		env->status = status_built_in;
		fprintf(stderr, "===INFO===: status_built_in = %d\n", env->status);
		return(status_built_in);
	}
	else if (bin_status != 0)
	{
		env->status = bin_status;
		fprintf(stderr, "===INFO===: bin_status = %d\n", env->status);
		return(bin_status);
	}
	
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
	char*	tmp_cmd;

	tmp = tk;
	tk_arg_to_table(tmp, arg_table);
	tmp_cmd = tmp->tk_str;
	// printf("tmp_cmd: %c\n", tmp_cmd[0]);
	if(tmp_cmd[0] == '/')
	{
		*cmd = tmp_cmd;
	}
	else
	{
		if (get_cmd_path(tmp) == SUCCESS)
		{
			tmp_str = ft_strjoin(tmp->path, "/");
			*cmd = ft_strjoin(tmp_str, tmp->tk_str);
			free(tmp_str);
		}
	}
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

	path = tk->path_tab;
	cmd = tk->tk_str;
	temp = NULL;
	i = 0;
	while (path[i] != 0)
	{
		temp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(temp, tk->tk_str);
		free(temp);
	
		if (check_access(cmd) == FAILURE)
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
	if (tk->next && tk->next->next && tk->next->type == TK_HERE_DOC && tk->next->next->type == TK_PIPE)
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
		fprintf(stderr, "===INFO===: in :: wait_all_pid: status = %d\n", status);
		status = get_status_info(status);
		tmp = get_next_type_tk(tmp, TK_CMD);
	}
	fprintf(stderr, "===INFO===: in :: wait_all_pid: status = %d\n", status);
	return (status);
}

int	get_status_info(int status)
{
	if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128; //convention bash: Si un programme est terminé par un signal, alors le code de sortie sera `128 + numéro du signal`
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	fprintf(stderr, "===INFO===: in :: get_status_info: status = %d\n", status);
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