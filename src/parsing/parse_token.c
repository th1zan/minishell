/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:26 by thibault          #+#    #+#             */
/*   Updated: 2023/08/22 21:24:52 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
		Analyser la liste
		1. Input
			-> operator
			-> token
		2. Classify operator
		4. Classifiy token
			-> If token contains quote
				-> Quoted token
				-> other token
		5. Analyse quoted token
			-> single quote token
			-> double quote token
		6. Handle single quote token
		7. Handle double quote token
		8. Handle newline token
		9. Handle blank token
		10. Handle word token
*/

	int	parse_token(t_tk **head_tk)
{
	// print_lst(*head_tk);
	ft_lst_modif_tk_str(*head_tk, del_whitespace);
	// print_lst(*head_tk);
	ft_lst_modif_tk_type(*head_tk, classify_operator);
	// print_lst(*head_tk);
	ft_delete_type_token(head_tk, TOKEN_BLANK);
	// print_lst(*head_tk);
	ft_lst_classify_tk_file(*head_tk);
	// print_lst(*head_tk);
	/*TODO: vérification des règles de grammaire ex: deux operateur à la suite-> pas possible*/
	ft_handle_file_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_arg_tk(*head_tk);
	// print_lst(*head_tk);
	ft_handle_hd_arg_tk(*head_tk);
	ft_delete_type_token(head_tk, TOKEN_HD_DELIM);
	print_lst(*head_tk);
	return (0);
}

int ft_delete_type_token(t_tk **tk, int tk_type)
{
	t_tk	*tmp;

	if (!(*tk))
		return (1);
	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == tk_type)
		{
			// printf("remove token %p\n", tmp);
			if (tmp->prev == NULL)
				*tk = tmp->next;
			tmp = ft_lst_remove(tmp);
			// printf("token deleted !\n");
		}
		else
			tmp = tmp->next;			
	}

		return (0);
}

int	check_file_operator(int type)
{
	if (type == TOKEN_APPEND_CHEVRON)
		return (1);
	else if (type == TOKEN_INPUT_CHEVRON)
		return (1);
	else if (type == TOKEN_OUTPUT_CHEVRON)
		return (1);
	return (0);
}


int	ft_handle_arg_tk(t_tk *tk)
{
	t_tk	*tk_cmd;
	t_tk	*tk_arg_first;
	t_tk	*tk_arg_last; // Dernier argument pour un TOKEN_COMMAND

	//classify token as COMMAND or ARGUMENT
	tk_cmd = tk;
	while (tk)
		{
			if (tk->type == TOKEN_COMMAND && tk->next)
			{
				tk = tk->next;
				while (tk && tk->type == TOKEN_COMMAND)
				{
					tk->type = TOKEN_ARGUMENT;
					tk = tk->next;
				}
			}
			tk = tk->next;
		}
	//move token to the sublist
	tk = tk_cmd;
	while (tk)
	{
		if (tk->type == TOKEN_COMMAND && tk->next)
		{
			tk_cmd = tk;
			tk = tk->next;
			
			tk_arg_first = tk;
			tk_arg_last = NULL;
			
			while (tk && tk->type == TOKEN_ARGUMENT)
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
	t_tk	*tk_hd;
	t_tk	*tk_arg;
	t_tk	*tk_entry_delim;
	t_tk	*tk_end_delim;

	if (!tk)
		return (1);

	while (tk)
	{	
		if (tk->type == TOKEN_HERE_DOC)
		{	
			tk_hd = tk;
			tk_entry_delim = tk->next;
			
			if (!tk_entry_delim || tk_entry_delim->type != TOKEN_HD_ARG)
			{
				printf("HERE-DOC delim error");
				return (1);
			}
			tk_entry_delim->type = TOKEN_HD_DELIM;

			tk_arg = tk_entry_delim->next;

			while (tk_arg && tk_arg->next && tk_arg->next->type == TOKEN_HD_ARG)
			{
				// printf("entry:%s arg:%s\n",tk_entry_delim->tk_str, tk_arg->next->tk_str);
				if (ft_strncmp(tk_entry_delim->tk_str, tk_arg->next->tk_str, 10) == 0)
				{	
					tk_arg = tk_arg->next;
					break;
				}
				tk_arg = tk_arg->next;
				
			}
			tk_end_delim = tk_arg;

			// printf("FINAL entry:%s arg:%s\n",tk_entry_delim->tk_str, tk_end_delim->tk_str);
			// printf("tk_hd: %p tk_arg: %p tk_entry_delim: %p tk_end_delim %p\n", tk_hd, tk_arg, tk_entry_delim, tk_end_delim);
			
			if (!tk_end_delim || ft_strncmp(tk_entry_delim->tk_str, tk_end_delim->tk_str, 10) != 0)
			{
				printf("HERE-DOC delim error");
				// printf("FINAL entry:%s arg:%s\n",tk_entry_delim->tk_str, tk_end_delim->tk_str);
				return (1);
			}
			
			tk_end_delim->type = TOKEN_HD_DELIM;

			tk_hd->tk_arg = tk_entry_delim->next;
			tk_entry_delim->next = tk_end_delim;
			tk_end_delim->prev->next = NULL;
			tk_end_delim->prev = tk_entry_delim;
			if (tk_end_delim->next)
				tk_end_delim->next->prev = tk_entry_delim;
			
		}
		tk = tk->next;
	}			
	return (0);
}


/*After the operator < > >> , there is a file. The file is an "argument" (sublist) of the operator*/
int	ft_handle_file_tk(t_tk *tk)
{

	t_tk *tk_file;
	
	if (!(tk))
		return (1);
	while (tk)
	{
		
		if (check_file_operator(tk->type) && tk->next)
		{
			tk_file = tk->next;
			tk_file->type = TOKEN_FILE;
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


int	del_whitespace(char **str)
{
	int		begin;
	int		end;
	int		len;
	char	*temp;

	if (!*str || **str == '\0')
		return (0);
	begin = 0;
	while(str[begin])
	{
		if (!str[begin])
			break;
		return(0);
	}
	begin = 0;
	while (is_whitespace((*str)[begin]))
		begin++;
	end = ft_strlen(*str) -1;
	while(is_whitespace((*str)[end]))
		end--;
	len = end - begin + 1;
	temp = *str;
	*str = ft_substr(temp, begin, len);
	free(temp);
	return (0);
}

int	classify_operator(char *str)
{
	if (*str == '\0')
		return (TOKEN_NULL);
	if(is_whitespace(*str))
		return(TOKEN_BLANK);
	if(is_here_doc(str, 0))
		return(TOKEN_HERE_DOC);
	if(is_redir_out_app(str, 0))
		return(TOKEN_APPEND_CHEVRON);
	if(is_redir_in(str, 0))
		return(TOKEN_INPUT_CHEVRON);
	if(is_redir_out(str, 0))
		return(TOKEN_OUTPUT_CHEVRON);
	if(is_pipe(str, 0))
		return(TOKEN_PIPE);
	// Error to handle if unhandled token
	if(is_onechar_delim(str, 0) || is_twochar_delim(str, 0))
		return(-2);
	return (TOKEN_UNCLASSIFIED);
}



// TEST Minishell
// < "file entree.txt" wc -l |         ls  -l << 'output de sortie'