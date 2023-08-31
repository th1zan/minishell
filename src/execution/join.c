/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:04:02 by mlachat           #+#    #+#             */
/*   Updated: 2023/08/31 16:55:20 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//1) parcourir liste token:
//2) si le token est de type CMD ->chercher cmd dans bin et fournir options & args.
//3) si le token est un opérateur ->prendre fichier en arg et l'ouvrir pour en faire un fd.

#include "../minishell.h"

// int		check_parsing(t_tk *tk)
// {
// 	t_tk	*tmp;
// 	t_tk	*prev;
// 	t_tk	*arg;
	
// 	if (!tk)
// 	{
// 		perror("error - no argument\n");
// 		return (0);
// 	}
// 	tmp = tk;
// 	prev = NULL;

// 	/*
// 	check main list:
// 	1st token: < > >> < OR TK_CMD
// 	2nd token: 
// 		a) any
// 		b) if prev = CMD -> next = < > >> < |
// 		c) if prev = < > >> < next = CMD
// 	loop until last token
//     last token: < > >> < | OR TK_CMD 
// 	*/
// 	if (!(is_tk_redir(tmp->type) || tmp->type == TK_CMD))
// 		perror("error: first TK is not redir_operator or CMD"); //
// 	prev = tmp;
// 	tmp = tmp->next;
// 	while (tmp != NULL)
// 	{
	
// 			printf("INFO: prev/type: %s/%d - current/type: %s/%d\n", prev->tk_str, prev->type, tmp->tk_str, tmp->type);
// 			if (prev->type == TK_CMD && !(is_tk_redir(tmp->type) || tmp->type == TK_PIPE))
// 				{
// 					printf("error: prev TK is CMD and current TK is not a redir_operator OR a pipe\n");
// 					return (1);
// 				}
// 			if ((is_tk_redir(prev->type) || prev->type == TK_PIPE) && tmp->type != TK_CMD)
// 				{
// 					printf("error: prev TK is a redir_operator OR a pipe and current TK is not CMD \n minishell: syntax error near unexpected token\n\n");
// 					return (1);
// 				}
// 			prev = tmp;
// 			tmp = tmp->next;
// 	}
// 	if (!(is_tk_redir(prev->type) || prev->type == TK_CMD || prev->type == TK_PIPE))
// 		perror("error: last TK is not redir_operator or CMD or PIPE");
	
// 	//check sub list:
	
// 	tmp = tk;
// 	arg = NULL;
// 	while (tmp != NULL)
// 	{

// 		if (is_tk_in_out_app(tmp->type)) // < > >> 1 seul arg, pas + et pas - -> TK_FILE 
// 		{
// 			if (tmp->tk_arg)
// 				arg = tmp->tk_arg;
// 			if (tmp->tk_arg == NULL || tmp->tk_arg->next != NULL)
// 			{
// 				printf("error: redirection operator without file\n");
// 				return (1);
// 			}
// 			if (tmp->tk_arg->type != TK_FILE)
// 			{
// 				printf("error: redirection operator has a wrong type arg\n");
// 				return (1);
// 			}
// 		}
// 		else if (tmp->type == TK_PIPE) // | : pas d'arg pour le pipe
// 		{
// 			if (tmp->tk_arg != NULL)
// 			{
// 				printf("error: pipe operator has an argument, it should not\n");
// 				return (1);
// 			}
// 		}
// 		else if (tmp->type == TK_HERE_DOC) 
// 		{
			
// 		//tout est possible, 0, 1, plusieurs arg. 
// 	    //args doivent être des TK_HD_ARG
// 		//cas de délimiteur début/fin non identiques est traité précédemment 
// 			*/
// 			if (tmp->tk_arg)
// 				arg = tmp->tk_arg;
// 			while (!arg)
// 			{
// 				if (arg->type != TK_HD_ARG)
// 				{
// 					printf("error: here-doc operator has a wrong type arg\n");
// 					return (1);
// 				}
// 				 arg = arg->next;
// 			}
// 		}
// 		else if (tmp->type == TK_CMD) 
// 		{
			
// 			//tout est possible: 0, 1, plusieurs arg. 
// 			//les args doivent être des TK_ARG
// 			//cas de délimiteur début/fin non identiques est traité précédemment 
			
// 			if (tmp->tk_arg)
// 				arg = tmp->tk_arg;
// 			while (!arg)
// 			{
// 				if (arg->type != TK_ARG)
// 				{
// 					printf("error: TK_CMD has a wrong type arg\n");
// 					return (1);
// 				}
// 				 arg = arg->next;
// 			}
// 		}

// 		tmp = tmp->next;
// 	}
// 	return (0);
// }