/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:26:16 by thibault          #+#    #+#             */
/*   Updated: 2023/10/07 16:56:21 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_arg_tk(t_tk *tk)
{
	t_tk	*tk_cmd;
	t_tk	*tk_arg_first;
	t_tk	*tk_arg_last; // Dernier argument pour un TOKEN_COMMAND

	//classify token as COMMAND or ARGUMENT
	tk_cmd = tk;
	while (tk)
		{
			if (tk->type == TK_CMD && tk->next)
			{
				tk = tk->next;
				while (tk && tk->type >= TK_CMD)
				{
					tk->type = TK_ARG;
					delete_quotes(&(tk->tk_str));
					tk = tk->next;
				}
			}
			if(tk)
				tk = tk->next;
		}
	//move token to the sublist
	tk = tk_cmd;
	while (tk)
	{
		if (tk->type == TK_CMD && tk->next && tk->next->type >= TK_CMD)
		{
			tk_cmd = tk;
			tk = tk->next;
			
			tk_arg_last = NULL;
			tk_arg_first = NULL;

			// if (tk->type == TOKEN_COMMAND)
				tk_arg_first = tk;
			
			while (tk && tk->type == TK_ARG)
			{
				tk_arg_last = tk;
				tk = tk->next;
			}
			tk_cmd->tk_arg = tk_arg_first;
			if (tk_arg_last)
			{
				tk_cmd->next = tk_arg_last->next;
				if (tk_arg_last->next)
					tk_arg_last->next->prev = tk_cmd;
				tk_arg_last->next = NULL;
			}
		}
		if (tk)
			tk = tk->next;
	}
	return (0);
}

int	ft_handle_hd_arg_tk(t_tk *tk)
{
	char	*input;
	char	*tmp_hd_arg_file;
	int		fd_tmp;

	tmp_hd_arg_file = "hd_arg.txt";
	// Supprimer le fichier
	unlink(tmp_hd_arg_file);
	fd_tmp = open(tmp_hd_arg_file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (fd_tmp == -1)
	{
		perror("Error opening file");
		return (1);
	}
	// printf("fd_tmp = %d\n", fd_tmp);
	if (!tk)
		return (1);
	while (tk)
	{	
		if (tk->type == TK_HD_ARG)
		{	
			while(1)
			{
				input = get_line("heredoc> ");
				if (!input)
				{
					printf("get_line returned NULL\n");
					continue;
				}
				// printf("Received input: %s\n", input); // Debug line
				if (!ft_strncmp(input, tk->tk_str, ft_strlen(tk->tk_str)))
					break;
				// printf("fd_tmp = %d\n", fd_tmp);
				ssize_t bytes_written = write(fd_tmp, input, ft_strlen(input));
				write(fd_tmp, "\n", 1);
				if (bytes_written == -1)
				{
					perror("Error writing to file");
				}

				// printf("Wrote %zd bytes to file\n", bytes_written); // Debug line
				free(input);
				tk->prev->tk_str = tmp_hd_arg_file;
			}
		}
		tk = tk->next;
	}			
	close(fd_tmp);
	return (0);
}


// int	ft_handle_hd_arg_tk(t_tk *tk)
// {
// 	char	*input;
// 	char	*tmp_hd_arg_file;
// 	int		fd_tmp;

// 	tmp_hd_arg_file = "hd_arg";
// 	fd_tmp = open(tmp_hd_arg_file, O_CREAT | O_APPEND, 0777);
// 	if (fd_tmp == -1)
// 		return (1);
// 	if (!tk)
// 		return (1);
// 	while (tk)
// 	{	
// 		if (tk->type == TK_HD_ARG)
// 		{	
// 			while(1)
// 			{
// 				ft_putstr_fd("heredoc> ", 1);
// 				input = get_line();
// 				if (!input)
// 					continue;
// 				if (!ft_strncmp(input, tk->tk_str, ft_strlen(tk->tk_str)))
// 					break;
// 				write(fd_tmp, input, ft_strlen(input));
// 				write(fd_tmp, "\n", 1);
// 				free(input);
// 			}
// 		}
// 		tk = tk->next;
// 	}			
// 	close(fd_tmp);
// 	// tk->tk_str = tmp_hd_arg_file;
// 	return (0);
// }


// ft_handle_hd_arg_tk(t_tk *tk)
// {
// 	t_tk	*tk_hd;
// 	t_tk	*tk_arg;
// 	t_tk	*tk_entry_delim;
// 	t_tk	*tk_end_delim;

// 	if (!tk)
// 		return (1);

// 	while (tk)
// 	{	
// 		if (tk->type == TK_HERE_DOC)
// 		{	
// 			tk_hd = tk;
// 			tk_entry_delim = tk->next;
			
// 			if (!tk_entry_delim || tk_entry_delim->type != TK_HD_ARG)
// 			{
// 				printf("HERE-DOC delim error");
// 				return (1);
// 			}
// 			tk_entry_delim->type = TK_HD_DELIM;

// 			tk_arg = tk_entry_delim->next;

// 			while (tk_arg && tk_arg->next && tk_arg->next->type == TK_HD_ARG)
// 			{
// 				// printf("entry:%s arg:%s\n",tk_entry_delim->tk_str, tk_arg->next->tk_str);
// 				if (ft_strncmp(tk_entry_delim->tk_str, tk_arg->next->tk_str, 10) == 0)
// 				{	
// 					tk_arg = tk_arg->next;
// 					break;
// 				}
// 				tk_arg = tk_arg->next;
				
// 			}
// 			tk_end_delim = tk_arg;

// 			// printf("FINAL entry:%s arg:%s\n",tk_entry_delim->tk_str, tk_end_delim->tk_str);
// 			// printf("tk_hd: %p tk_arg: %p tk_entry_delim: %p tk_end_delim %p\n", tk_hd, tk_arg, tk_entry_delim, tk_end_delim);
			
// 			if (!tk_end_delim || ft_strncmp(tk_entry_delim->tk_str, tk_end_delim->tk_str, 10) != 0)
// 			{
// 				printf("HERE-DOC delim error");
// 				// printf("FINAL entry:%s arg:%s\n",tk_entry_delim->tk_str, tk_end_delim->tk_str);
// 				return (1);
// 			}
			
// 			tk_end_delim->type = TK_HD_DELIM;

// 			tk_hd->tk_arg = tk_entry_delim->next;
// 			tk_entry_delim->next = tk_end_delim;
// 			tk_end_delim->prev->next = NULL;
// 			tk_end_delim->prev = tk_entry_delim;
// 			if (tk_end_delim->next)
// 				tk_end_delim->next->prev = tk_entry_delim;
			
// 		}
// 		tk = tk->next;
// 	}			
// 	return (0);
// }

/*After the operator < > >> , there is a file. The file is an "argument" (sublist) of the operator*/
int	ft_handle_file_tk(t_tk *tk)
{

	t_tk *tk_file;
	
	if (!(tk))
		return (1);
	while (tk)
	{
		
		if (is_tk_in_out_app(tk->type) && tk->next)
		{
			tk_file = tk->next;
			tk_file->type = TK_FILE;
			tk->next = tk_file->next;
			tk->tk_arg = tk_file;
			if (tk_file->next)
			{
				tk_file->next->prev = tk;
			}
			tk_file->next = NULL;
			
		}
		tk = tk->next;
			
	}
		// printf("OUT-> str:%s type: %d \n", tk->tk_str, tk->type);
		return (0);

	// TODO: Gérer les erreur : 
	// - operateur de redirecton non suivi par un nom de fichier: syntax error: unexpected end of file
	// - opérateur suivi par plus de 1 nom de fichier 
	// - nom de fichier invalide
	
}


int	ft_handle_built_in(t_tk *tk)
{

	t_tk *tmp;
	
	if (!(tk))
		return (1);
	tmp = tk;
	while (tmp)
	{
		
		if (tmp->type == TK_CMD)
		{
			if(is_builtin_cmd_tk(tmp) == 1)
			{
				tmp->type = TK_CMD_BUILT_IN;
				// printf("%d : TK %s is a BUILT IN\n", is_builtin_cmd_tk(tmp), tmp->tk_str);
			}
		}
		tmp = tmp->next;
	}
		// printf("OUT-> str:%s type: %d \n", tk->tk_str, tk->type);
		return (0);

	
}