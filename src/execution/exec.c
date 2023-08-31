/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:11:53 by mlachat           #+#    #+#             */
/*   Updated: 2023/09/01 01:11:06 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


int	execution(t_tk **tk)
{
	char		*tk_str;	// contenu du token
	int			type;		// type du token 
	int			fd_in;		
	int			fd_out;
	char		*arg_tk_str;	//argument du token
	t_tk		*tmp;

	
	tmp = *tk;
	if (tmp)
	{
		tk_str = tmp->tk_str;
		type = tmp->type;
		fd_in = tmp->fd_in;
		fd_out = tmp->fd_out;
		arg_tk_str = NULL;

	}

	printf("On est dans la fonction execution:\n");
	print_lst(*tk);

	// Print list
	while (tmp != NULL)
	{
		if (tmp)
		{
			tk_str = tmp->tk_str;
			type = tmp->type;
			fd_in = tmp->fd_in;
			fd_out = tmp->fd_out;
			arg_tk_str = arg_to_str(tmp);
		}
		printf("tk_str:%s, type:%d, fd_in:%d, fd_out:%d, arg_tk_str:%s\n", tk_str, type, fd_in, fd_out, arg_tk_str);
		// printf("tmp->next:%p\n", tmp->next);
   		if(tmp->next)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
	free (arg_tk_str);


	
	//1. get_fd
	//2. execute_cmd
	// 2.1 get_cmd_arg
	// 2.2 pipe ???
	// 2.3 fork
	// 2.4 execv
	// 3. wait_pid


	return (0);
}

// void	execution(t_env *env)
// {
// 	t_token	*token;
// 	int		status;
// 	int		status_built;

// 	if (env->verbose == 1)
// 		ft_printf("=== Execution ===\n");
// 	token = get_first_token_cmd(env);
// 	while (token)
// 	{
// 		status_built = execute_cmd(env, token);
// 		token = get_next_token_cmd(token);
// 	}
// 	close_all_fd(env);
// 	status = wait_all_pid(env);
// 	status = get_last_status(status, status_built);
// 	update_variable_status_process(env, status);
// 	if (env->verbose == 1)
// 		ft_printf("=========\n");
// }

/*
cmd = get_first_cmd(env);
while (cmd)
{
	bin_execution(env, cmd);
	cmd = get_next_cmd(cmd);
}
close_all_fd(env);
wait_all_pid(env);


void bin_execution(t_env *env, t_cmd *cmd)
{
    int pid;

    pid = fork();
    if (pid == 0)
    {
	redirect_cmd(cmd);
	close_all_fd(env);
	execve(path, args, variables);
    }
    else
    {
	stock_pid(cmd, id);
        return ;
    }
}

int	execute_cmd(t_env *env, t_token *token)
{
	t_cmd	*cmd;
	char	**variables;
	int		status_built;

	status_built = -1;
	cmd = get_class(token);
	if (is_cmd_bin(cmd))
	{
		variables = get_env_variables(env);
		bin_execution(env, cmd, variables);
	}
	else if (is_cmd_built_in(cmd))
	{
		status_built = built_in_execution(env, cmd);
	}
	return (status_built);
}

int	wait_all_pid(t_env *env)
{
	t_token	*token;
	t_cmd	*cmd;
	int		status;

	token = get_first_token_bin(env);
	status = 0;
	while (token)
	{
		cmd = get_class(token);
		waitpid(cmd->pid, &status, 0);
		status = convert_status_process_value(status);
		token = get_next_token_bin(token);
	}
	return (status);
}
*/