/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:34:44 by thibault          #+#    #+#             */
/*   Updated: 2023/09/17 12:42:19 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
	1. set pipes for TK_PIPE pipe[2] => pipe[1] (will be writed) >===PIPE===> pipe[0] (will be read) 
	2. set redirection for standard input/output
	3. set fd in/out for TK_CMD (fd_in = last_tk->pipe[0]),  (fd_out = next_tk->pipe[1])
*/

int	set_redirection(t_tk **tk)
{
	printf("1)\n");
	set_pipe(tk);
	printf("2)\n");
	set_cmd_fd(tk);
	printf("3)\n");
	print_lst(*tk);
	set_stdin_out(tk);
	printf("4)\n");
	return (0);
}

int	set_cmd_fd(t_tk **tk)
{
	t_tk		*tmp;
	t_tk		*prev_pipe;
	t_tk		*next_pipe;

	tmp = *tk;
	prev_pipe = NULL;
	next_pipe = NULL;
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD)
		{
			prev_pipe = get_prev_type_tk(tmp, TK_PIPE);
			next_pipe = get_next_type_tk(tmp, TK_PIPE);
			if (prev_pipe)
				tmp->fd_in = prev_pipe->fd_out;
			if (next_pipe)
				tmp->fd_out = next_pipe->fd_in;	
		}
		tmp = tmp->next;
	}		
	
	return (0);
}

int	set_stdin_out(t_tk **tk)
{
	t_tk		*tmp;
	char		*file;

	//if redirection operator => set new fd for input and output
	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_IN_CHEVRON)
		{
			file = tmp->tk_arg->tk_str;
			redirect_std_in_out(file, O_RDONLY, STDIN_FILENO);
		}
		else if (tmp->type == TK_OUT_CHEVRON)
		{
			file = tmp->tk_arg->tk_str;
			redirect_std_in_out(file, O_CREAT, STDOUT_FILENO);
			printf("test\n");
		}
		else if (tmp->type == TK_APP_CHEVRON)
		{
			file = tmp->tk_arg->tk_str;
			redirect_std_in_out(file, O_CREAT | O_APPEND, STDOUT_FILENO);
		}
		else if (tmp->type == TK_HERE_DOC)
		{
			//Gestion HERE-DOC à faire
		}		
		printf("tmp_add:%p\n", tmp);
		tmp = tmp->next;
	}
	return (0);
}

int	redirect_std_in_out(char *file, int option, int std)
{
	int fd;

	if (option == O_CREAT || option == (O_CREAT | O_APPEND))
		fd = open(file, option, 0777);
	else
		fd = open(file, option);

	fd = open(file, option);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return 1;
	}
	if (dup2(fd, std) == -1)
	{
		perror("Erreur lors de la redirection");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
 
int	set_pipe(t_tk **tk)
{
	t_tk		*tmp;
	int			pipe_tab[2];
	

	//set pipes
	// 	/*
	// 	Pipe creation:
	// 		pipe_tab[0] will be read
	// 		pipe_tab[1] will be writed
	// 	*/
	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_PIPE)
		{
				if (pipe(pipe_tab) == -1)
				{
					perror("Failed to create the pipe");
					return (-1);
				}
				tmp->fd_in = pipe_tab[0];
				tmp->fd_out = pipe_tab[1];
		}
		tmp = tmp->next;
	}		
	
	return (0);
}


t_tk	*get_next_type_tk(t_tk *tmp, int type)
{
	t_tk	*next_tk;

	next_tk = NULL;
	tmp = tmp->next;
	while(tmp)
	{
		if (tmp->type == type)
		{
			next_tk = tmp;
			break;
		}
		tmp = tmp->next;
	}
	return (next_tk);
}

t_tk	*get_prev_type_tk(t_tk *tmp, int type)
{
	t_tk	*prev_tk;

	prev_tk = NULL;
	tmp = tmp->next;
	while(tmp)
	{
		if (tmp->type == type)
		{
			prev_tk = tmp;
			break;
		}
		tmp = tmp->next;
	}
	return (prev_tk);
}

	
	// tmp = *tk;
	// if (tmp)
	// {
	// 	tk_str = tmp->tk_str;
	// 	type = tmp->type;
	// 	fd_in = tmp->fd_in;
	// 	fd_out = tmp->fd_out;
	// 	arg_tk_str = NULL;

	// }

	// printf("On est dans la fonction redirection:\n");
	// print_lst(*tk);

	// // Print list
	// while (tmp != NULL)
	// {
	// 	if (tmp)
	// 	{
	// 		tk_str = tmp->tk_str;
	// 		type = tmp->type;
	// 		fd_in = tmp->fd_in;
	// 		fd_out = tmp->fd_out;
	// 		arg_tk_str = arg_to_str(tmp);
	// 	}
	// 	printf("tk_str:%s, type:%d, fd_in:%d, fd_out:%d, arg_tk_str:%s\n", tk_str, type, fd_in, fd_out, arg_tk_str);
	// 	// printf("tmp->next:%p\n", tmp->next);
   	// 	if(tmp->next)
	// 		tmp = tmp->next;
	// 	else
	// 		tmp = NULL;
	// }
	// free (arg_tk_str);


	
	//1. get_fd
	//2. execute_cmd
	// 2.1 get_cmd_arg
	// 2.2 pipe ???
	// 2.3 fork
	// 2.4 execv
	// 3. wait_pid
