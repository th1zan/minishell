/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:34:44 by thibault          #+#    #+#             */
/*   Updated: 2023/09/22 12:12:49 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
	1. set pipes for TK_PIPE pipe[2] => pipe[1] (will be writed) >===PIPE===> pipe[0] (will be read) 
	2. set redirection for standard input/output
	3. set fd in/out for TK_CMD (fd_in = last_tk->pipe[0]),  (fd_out = next_tk->pipe[1])
*/

// < IN_file grep a | wc -l > OUT_file

int	set_redirection(t_tk **tk)
{
	
	set_default_fd(tk);
	set_pipe_fd(tk);
	set_operator_fd(tk);
	set_cmd_std_fd(tk);
	set_cmd_pipe_fd(tk);
	set_cmd_operator_fd(tk);
	redir_operator_fd(tk);
	fprintf(stderr, "LST PRINT AFTER REDIRECTION\n");
	print_lst(*tk);
	return (0);
}
int	set_default_fd(t_tk **tk)
{
	t_tk		*tmp;
	
	tmp = *tk;
	while (tmp != NULL)
	{
		tmp->fd_in = -1;
		tmp->fd_out = -1;
		tmp = tmp->next;
	}		
	
	return (0);
}


int	set_pipe_fd(t_tk **tk)
{
	t_tk		*tmp;
	int			pipe_tab[2];
	

	//set pipes
	// 	/*
	// 	Pipe creation:
	// 		pipe_tab[0] is the read end of the pipe
	// 		pipe_tab[1] is the written end of the pipe
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
				tmp->fd_in = pipe_tab[1];
				tmp->fd_out = pipe_tab[0];
				printf("pipe_tab[0]: %d, pipe_tab[1]: %d \n", pipe_tab[0], pipe_tab[1]);
		}
		tmp = tmp->next;
	}		
	
	return (0);
}


int	set_operator_fd(t_tk **tk)
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
			close(tmp->fd_in);
			tmp->fd_in = open_file_to_fd(file, O_RDONLY);
			// fprintf(stderr,"tmp:%p fd_in:%d fd_out:%d\n", tmp, tmp->fd_in, tmp->fd_out);
		}
		else if (tmp->type == TK_OUT_CHEVRON)
		{
			file = tmp->tk_arg->tk_str;
			close(tmp->fd_out);
			tmp->fd_out = open_file_to_fd(file, O_CREAT | O_WRONLY | O_TRUNC);
			// fprintf(stderr,"tmp:%p fd_in:%d fd_out:%d\n", tmp, tmp->fd_in, tmp->fd_out);
		}
		else if (tmp->type == TK_APP_CHEVRON)
		{
			file = tmp->tk_arg->tk_str;
			close(tmp->fd_out);
			tmp->fd_out = open_file_to_fd(file, O_CREAT | O_APPEND);
			// fprintf(stderr,"tmp:%p fd_in:%d fd_out:%d\n", tmp, tmp->fd_in, tmp->fd_out);
		}
		else if (tmp->type == TK_HERE_DOC)
		{
			//Gestion HERE-DOC à faire
		}		
		// printf("tmp analized in set_operator_fd:%p\n", tmp);
		tmp = tmp->next;
	}
	return (0);
}

int open_file_to_fd(char *file, int option)
{
	int fd;


	fd = open(file, option, 0777);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (-1);
	}
	fprintf(stderr, "open fd : %d\n", fd);
	return (fd);
}

int	redir_operator_fd(t_tk **tk)
{
	t_tk		*tmp;

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_IN_CHEVRON)
		{
			// close(tmp->fd_out);
			// fprintf(stderr, "close : %d\n", tmp->fd_out);
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			{
				perror("dup2 error: fd_in in redir_operator_fd");
				fprintf(stderr, "d_in: %d, errno: %d\n", tmp->fd_in, errno);
				return (-1);
			}
			fprintf(stderr, "redir_operator_fd :: dup2 %d : %d\n", tmp->fd_in, STDIN_FILENO);
			// close(tmp->fd_in);
			// fprintf(stderr, "close : %d\n", tmp->fd_in);
			
		}
		else if (tmp->type == TK_HERE_DOC)
		{
			// Cas à traiter
		}
		else if (tmp->type == TK_OUT_CHEVRON || tmp->type == TK_APP_CHEVRON)
		{
			// close(tmp->fd_in);
			// fprintf(stderr, "close : %d\n", tmp->fd_in);
			if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2 error: fd_out in redir_operator_fd");
				fprintf(stderr, "fd_out: %d, errno: %d\n", tmp->fd_out, errno);
				return (-1);
			}
			fprintf(stderr, "fredir_operator_fd :: dup2 %d : %d\n", tmp->fd_out, STDOUT_FILENO);
			// close(tmp->fd_out);
			// fprintf(stderr, "close : %d\n", tmp->fd_out);
		}
		tmp = tmp->next;
	}		
	
	return (0);
}

int	set_fd_for_cmd(t_tk *tk)
{
	fprintf(stderr, "function:set_fd_for_cmd::\n");
	fprintf(stderr, "tk: %s \n", tk->tk_str);

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
			fprintf(stderr, "set_fd_for_cmd :: fd_in dup2 %d : %d\n", fd_in, STDIN_FILENO);
		}
	}
	if (tk->next && tk->next->type == TK_PIPE)
	{
		//PAS DE close() ICI
		if (fd_is_standard(fd_out) == 0)
		{
			
			if (dup2(fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2 error: fd_out in set_fd_for_cmd");
				fprintf(stderr, "set_fd_for_cmd :: fd_out: %d, errno: %d\n", fd_out, errno);
				return (-1);
			}
		}
			fprintf(stderr, "set_fd_for_cmd :: fd_out dup2 %d : %d\n", fd_out, STDOUT_FILENO);
	}
	return (0);
}


// int set_fd_for_cmd(t_tk *tk)
// {
// 	t_tk *tmp_prev;
// 	t_tk *tmp_next;


// 	tmp_prev = tk->prev;
// 	tmp_next = tk->next;

// 	printf("tk: %s \n", tk->tk_str);
// 	printf("tmp_prev: %p \n", tmp_prev);
// 	printf("tmp_next: %p \n", tmp_next);

// 	if (tmp_prev != NULL)
// 	{
// 		printf("dup2(tmp_prev->fd_out: %d, STDIN: %d)\n",tmp_prev->fd_out, STDIN_FILENO );
// 		if (tmp_prev->type == TK_PIPE)
// 		{
// 			if (tmp_prev->fd_in != -1)
// 			{	
// 				if (dup2(tmp_prev->fd_out, STDIN_FILENO) == -1)
// 				{
// 					perror("dup2 error 1");
// 					fprintf(stderr, "errno: %d\n", errno);
// 					return (-1);
// 				}
// 				// close(tmp_prev->fd_out);
// 				// close(tmp_prev->fd_in);
// 			}
// 			else
// 				perror("fd = -1");

// 		}
// 	}

// 	if (tmp_next != NULL)
// 	{
// 		printf("dup2 (tmp_next->fd in: %d , STDOUT: %d)\n",tmp_next->fd_in, STDOUT_FILENO);
// 		if (tmp_next->type == TK_PIPE)
// 		{
// 			if (tmp_next->fd_in != -1)
// 			{	
// 				if (dup2(tmp_next->fd_in, STDOUT_FILENO) == -1)
// 				{
// 					perror("dup2 error 3");
// 					return (-1);
// 				}
// 				// close(tmp_next->fd_in);
// 				// close(tmp_next->fd_out);
// 			}
// 			else
// 				perror("fd = -1");
// 		}
// 	}
// 	return (0);
// }

// =================================

int	set_cmd_std_fd(t_tk **tk)
{
	t_tk		*tmp;
	
	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD)
		{
			if (tmp->prev == 0)
				tmp->fd_in = STDIN_FILENO;
			if (tmp->next == 0)
				tmp->fd_out = STDOUT_FILENO;
		}
		tmp = tmp->next;
	}		
	
	return (0);
}

int	set_cmd_pipe_fd(t_tk **tk)
{
	t_tk *tmp;
	t_tk *prev_pipe;
	t_tk *next_pipe;

	tmp = *tk;
	while (tmp != NULL)
	{
		// Réinitialisation des variables à chaque itération
		prev_pipe = NULL;
		next_pipe = NULL;

		if (tmp->type == TK_CMD)
		{
			// Vérification de l'existence de tmp->prev avant de vérifier son type
			if (tmp->prev && tmp->prev->type == TK_PIPE)
				prev_pipe = tmp->prev;

			// Vérification de l'existence de tmp->next avant de vérifier son type
			if (tmp->next && tmp->next->type == TK_PIPE)
				next_pipe = tmp->next;

			if (prev_pipe)
				tmp->fd_in = prev_pipe->fd_out;

			if (next_pipe)
				tmp->fd_out = next_pipe->fd_in;
		}
		tmp = tmp->next;
	}

	return (0);
}

int set_cmd_operator_fd(t_tk **tk)
{
	t_tk *tmp;
	t_tk *prev_operator;
	t_tk *next_operator;

	tmp = *tk;
	while (tmp != NULL)
	{
		// Réinitialisation des variables à chaque itération
		prev_operator = NULL;
		next_operator = NULL;

		if (tmp->type == TK_CMD)
		{
			// Vérification de l'existence de tmp->prev avant de vérifier son type
			if (tmp->prev && (tmp->prev->type == TK_IN_CHEVRON || tmp->prev->type == TK_HERE_DOC))
				prev_operator = tmp->prev;

			// Vérification de l'existence de tmp->next avant de vérifier son type
			if (tmp->next && (tmp->next->type == TK_OUT_CHEVRON || tmp->next->type == TK_APP_CHEVRON))
				next_operator = tmp->next;

			if (prev_operator)
				tmp->fd_in = prev_operator->fd_in;

			if (next_operator)
				tmp->fd_out = next_operator->fd_out;
		}

		tmp = tmp->next;
	}

	return (0);
}


int	close_tk_fd(t_tk *tk)
{
	t_tk		*tmp;

	tmp = tk;
	
	if ((tmp->fd_in != -1) && (fd_is_standard(tmp->fd_in) == 0))
	{
		close(tmp->fd_in);
		fprintf(stderr, "close : %d\n", tmp->fd_in);
		tmp->fd_in = -1;
	}
	if ((tmp->fd_out != -1) && (fd_is_standard(tmp->fd_out) == 0))
	{
		close(tmp->fd_out);
		fprintf(stderr, "close : %d\n", tmp->fd_out);
		tmp->fd_out = -1;
	}

	return (0);
}

int	close_all_fd(t_tk **tk)
{
	t_tk		*tmp;
	int         ret;  // Variable pour stocker le retour de close

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
				fprintf(stderr, "close_all_fd :: close : %d\n", tmp->fd_in);
				tmp->fd_in = -1;
			}
			if ((tmp->fd_out != -1) && (fd_is_standard(tmp->fd_out) != 1))
			{
				ret = close(tmp->fd_out);
				if (ret == -1) {
					perror("Error closing fd_out");
				}
				fprintf(stderr, "close_all_fd :: close : %d\n", tmp->fd_out);
				tmp->fd_out = -1;
			}
		}
		tmp = tmp->next;
	}
	return (0);
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

t_tk	*get_prev_type_tk(t_tk *tmp, int type)
{
	t_tk	*prev_tk;

	prev_tk = NULL;
	tmp = tmp->prev;
	while(tmp)
	{
		if (tmp->type == type)
		{
			prev_tk = tmp;
			break;
		}
		tmp = tmp->prev;
	}
	return (prev_tk);
}

int	save_std(int *original_std)
{
	original_std[0] = dup(STDIN_FILENO);
	original_std[1] = dup(STDOUT_FILENO);
	original_std[2] = dup(STDERR_FILENO);
	if (original_std[0] == -1 || original_std[1] == -1 || original_std[2] == -1)
	{
		perror("dup error: original_std[0] in save_std");
		fprintf(stderr, "errno: %d\n", errno);
		return (-1);
	}
	return 0;
}



int	restore_std(int *original_std)
{
	if (dup2(original_std[0], STDIN_FILENO) == -1)
	{
		perror("dup2 error: original_std[0] in restore_std");
		fprintf(stderr, "original_std[0]: %d, errno: %d\n", original_std[0], errno);
		return (-1);
	}	
	if (dup2(original_std[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 error: original_std[1] in restore_std");
		fprintf(stderr, "original_std[1]: %d, errno: %d\n", original_std[1], errno);
		return (-1);
	}	
	if (dup2(original_std[2], STDERR_FILENO) == -1)
	{
		perror("dup2 error: original_std[2] in restore_std");
		fprintf(stderr, "original_std[2]: %d, errno: %d\n", original_std[2], errno);
		return (-1);
	}
	close(original_std[0]);
	close(original_std[1]);
	close(original_std[2]);
	return 0;
}