/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:34:44 by thibault          #+#    #+#             */
/*   Updated: 2023/09/27 17:31:49 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_redirection(t_tk **tk)
{
	set_default_fd(tk);
	set_pipe_fd(tk);
	set_operator_fd(tk);
	set_cmd_std_fd(tk);
	set_cmd_pipe_fd(tk);
	set_cmd_operator_fd(tk);
	redir_operator_fd(tk);
	// print_lst(*tk);
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
	// 		pipe_tab[0] is the read side of the pipe
	// 		pipe_tab[1] is the written side of the pipe
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
				// printf("pipe_tab[0]: %d, pipe_tab[1]: %d \n", pipe_tab[0], pipe_tab[1]);
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
			file = tmp->tk_str;
			close(tmp->fd_in);
			tmp->fd_in = open_file_to_fd(file, O_RDONLY);
			fprintf(stderr,"tmp:%p fd_in:%d fd_out:%d\n", tmp, tmp->fd_in, tmp->fd_out);
		}
		
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
	// fprintf(stderr, "open fd : %d\n", fd);
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
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			{
				perror("dup2 error: fd_in in redir_operator_fd");
				fprintf(stderr, "d_in: %d, errno: %d\n", tmp->fd_in, errno);
				return (-1);
			}
			// fprintf(stderr, "redir_operator_fd :: dup2 %d : %d\n", tmp->fd_in, STDIN_FILENO);	
		}
		else if (tmp->type == TK_HERE_DOC)
		{
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			{
				perror("dup2 error: fd_in in redir_operator_fd");
				fprintf(stderr, "d_in: %d, errno: %d\n", tmp->fd_in, errno);
				return (-1);
			}
		}
		else if (tmp->type == TK_OUT_CHEVRON || tmp->type == TK_APP_CHEVRON)
		{
			if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2 error: fd_out in redir_operator_fd");
				fprintf(stderr, "fd_out: %d, errno: %d\n", tmp->fd_out, errno);
				return (-1);
			}
			// fprintf(stderr, "fredir_operator_fd :: dup2 %d : %d\n", tmp->fd_out, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}		
	return (0);
}

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
			if (tmp->prev && (tmp->prev->type == TK_IN_CHEVRON))
				prev_operator = tmp->prev;

			// Vérification de l'existence de tmp->next avant de vérifier son type
			if (tmp->next && (tmp->next->type == TK_OUT_CHEVRON || tmp->next->type == TK_APP_CHEVRON))
				next_operator = tmp->next;
			
			//Cas du Here-doc spécial. le HD est placé après la fonction mais compte comme une input
			if (tmp->next && (tmp->next->type == TK_HERE_DOC))
				prev_operator = tmp->next;

			if (prev_operator)
				tmp->fd_in = prev_operator->fd_in;

			if (next_operator)
				tmp->fd_out = next_operator->fd_out;
		}

		tmp = tmp->next;
	}
	return (0);
}




/*
FCT A SUPPRIMER

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
*/
