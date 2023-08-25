/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/08/25 17:06:45 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_token(t_tk **head_tk)
{
	// print_lst(*head_tk);
	ft_lst_modif_tk_str(*head_tk, del_whitespace);
	// print_lst(*head_tk);
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	// print_lst(*head_tk);
	ft_delete_type_token(head_tk, TK_BLANK);
	// print_lst(*head_tk);
	ft_lst_classify_tk_file(*head_tk);
	// print_lst(*head_tk);
	/*TODO: vérification des règles de grammaire ex: deux operateur à la suite-> pas possible*/
	ft_handle_file_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_arg_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_hd_arg_tk(*head_tk);
	ft_delete_type_token(head_tk, TK_HD_DELIM);
	print_lst(*head_tk);
	check_parsing(*head_tk);
	printf("fin du parsing\n");

	return (0);
}

int		check_parsing(t_tk *tk)
{
	t_tk	*tmp;
	t_tk	*prev;
	t_tk	*arg;
	
	if (!tk)
	{
		printf("error - no argument\n");
		return (0);
	}
	tmp = tk;
	prev = NULL;

	/*
	    check main list:
		first token: < > >> < OR TK_CMD
		second token : 
			a) any
			b) if prev = CMD -> next = < > >> < |
			c) if prev = < > >> < next = CMD
		loop until last token

		last token : < > >> < | OR TK_CMD 
	*/
	
	if (!(is_tk_redir(tmp->type) || tmp->type == TK_CMD))
	{
		printf("error: first TK is not redir_operator or CMD"); 
		return (1);
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp != NULL)
	{
	
			// printf("INFO: prev/type: %s/%d - current/type: %s/%d\n", prev->tk_str, prev->type, tmp->tk_str, tmp->type);
			if (prev->type == TK_CMD && !(is_tk_redir(tmp->type) || tmp->type == TK_PIPE))
				{
					printf("error: prev TK is CMD and current TK is not a redir_operator OR a pipe\n");
					return (1);
				}
			if ((is_tk_redir(prev->type) || prev->type == TK_PIPE) && tmp->type != TK_CMD)
				{
					printf("error: prev TK is a redir_operator OR a pipe and current TK is not CMD \n minishell: syntax error near unexpected token\n\n");
					return (1);
				}
			prev = tmp;
			tmp = tmp->next;
	}
	if (!(is_tk_redir(prev->type) || prev->type == TK_CMD || prev->type == TK_PIPE))
		perror("error: last TK is not redir_operator or CMD or PIPE");

	/*
	    check sub list:
	*/
	tmp = tk;
	arg = NULL;
	while (tmp != NULL)
	{
		arg = tmp->tk_arg;
		if (is_tk_in_out_app(tmp->type)) // < > >> un SEUL arg, pas plus et pas moins-> TK_FILE 
		{				
			if (tmp->tk_arg == NULL || tmp->tk_arg->next != NULL)
			{
				printf("error: redirection operator without file\n");
				return (1);
			}
			if (tmp->tk_arg->type != TK_FILE)
			{
				printf("error: redirection operator has a wrong type arg\n");
				return (1);
			}
		}
		else if (tmp->type == TK_PIPE) // | : pas d'argument pour le pipe
		{
			if (tmp->tk_arg != NULL)
			{
				printf("error: pipe operator has an argument, it should not\n");
				return (1);
			}
		}
		else if (tmp->type == TK_HERE_DOC) 
		{
			/*
			- tout est possible, 0, 1, plusieurs arg. 
			- les arg doivent être des TK_HD_ARG
			- Le cas de délimiteur début/fin non identiques est traité précédemment 
			*/
			while (arg)
			{
				if (arg->type != TK_HD_ARG)
				{
					printf("error: here-doc operator has a wrong type arg\n");
					return (1);
				}
				 arg = arg->next;
			}
		}
		else if (tmp->type == TK_CMD) 
		{
			/*
			- tout est possible, 0, 1, plusieurs arg. 
			- les arg doivent être des TK_ARG
			- Le cas de délimiteur début/fin non identiques est traité précédemment 
			*/ 

			while (arg)
			{
				
				if (arg && arg->type != TK_ARG)
				{
					printf("error: TK_CMD has a wrong type arg\n");
					return (1);
				}
				arg = arg->next;
			}
		}

		tmp = tmp->next;
	}
	return (0);
}




// TEST Minishell
// < "file entree.txt" wc -l |         ls  -l << 'output de sortie'