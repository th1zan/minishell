/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/11/01 15:32:51 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
delimiter tab:  tab of int
lenght of delimiter tab: length of input string
if tab[i] == 1 -> input[i] == delimiter
Then 


*/


static void	handle_delimiter_quotes(char *input, int *i)
{
	int		start_quote;
	char	tmp_quote;
	int	len;

	len = ft_strlen(input);
	start_quote = *i;
	tmp_quote = input[*i];
	(*i)++;
	while (*i < len)
	{
		if (input[*i] == tmp_quote)
		{
			
			break;
		}
		(*i)++;
	}
	if (*i == len)
		*i = start_quote + 1;
}

static void	process_character(char *input, int *delimiter, int *i)
{
	int	len;

	len = ft_strlen(input);

	delimiter[*i] = 1;
	// printf("input[%d]:%c is delimiter[%d]:%d \n", *i, input[*i], *i, delimiter[*i]);
	if (is_quote(input, *i))
	{
		handle_delimiter_quotes(input, i);
	}
	(*i)++;
	while (*i < len)
	{
		if (is_quote(input, *i))
		{
			handle_delimiter_quotes(input, i);
			
		}
		if (!ft_isprint(input[*i]) || is_whitespace(input[*i])|| input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
			break;
		(*i)++;
	}
	
}

static void	initialize_delimiters(char *input, int *delimiter)
{
	int	i;
	int	len;

	len = ft_strlen(input);
	i = 0;
	while (i < len)
	{
		
		if (is_whitespace(input[i]))
		{
			delimiter[i] = 1;
			// printf("input[%d]:%c is delimiter[%d]:%d \n", i, input[i], i, delimiter[i]);
			i++;
			while (i < len && is_whitespace(input[i]))
				i++;
		}
		else if (input[i] == '|')
		{
			delimiter[i] = 1;
			// printf("input[%d]:%c is delimiter[%d]:%d \n", i, input[i], i, delimiter[i]);
			i++;
		}
		else if (input[i] == '<')
		{	
			delimiter[i] = 1;
			// printf("input[%d]:%c is delimiter[%d]:%d \n", i, input[i], i, delimiter[i]);
			i++;
			if(input[i] && input[i] == '<')
				i++;
		}
		else if (input[i] == '>')
		{	
			delimiter[i] = 1;
			// printf("input[%d]:%c is delimiter[%d]:%d \n", i, input[i], i, delimiter[i]);
			i++;
			if(input[i] && input[i] == '>')
				i++;
		}
		else if (ft_isprint(input[i]) && input[i] != ' ')
		{
			process_character(input, delimiter, &i);
			
		}
		else
		{
			i++;
		}
	}
}

int	*get_delimiter(char *input)
{
	int	*delimiter;
	int	len;

	len = ft_strlen(input);
	delimiter = (int *)ft_calloc(len + 1, sizeof(int));
	if (!delimiter)
		return (NULL);
	initialize_delimiters(input, delimiter);

	// DEBUG
	// int i = 0;
	// while(i <= len)
	// {
	// 	printf("input[%d]:%c is delimiter[%d]:%d \n", i, input[i], i, delimiter[i]);
	// 	i++;
	// }

	
	return (delimiter);
}




int	input_to_token(char *input, char ***envp, t_tk **tk_head, int *delimiter)
{
	// input = "ls | wc"
	// delimiter = {0, 0, 0, 1, 0, 0, 0}
	int		begin; //delimiter: tab[0] = begin, tab[1] = end
	int		i;
	int		len;
	char	*tk_str;
	// char	**path_tab;
	*tk_head = NULL;
	begin = 0;
	len = 0;

	
	// path_tab = global_env->env_main;
	// printf("IN INPUT TO TOKEN");
	// print_strtab(global_env->path_tab);
	i = 0;
	while (input[i] != 0)
	{
		// printf("%d: %c del:%d\n", i, input[i], delimiter[i]);
		if (delimiter[i])
		{
			len = i - begin;
			// printf("%d: begin:%d len:%d\n", i, begin, len);
			if (len > 0)
			{
				// begin = 0
				// len = 3
				tk_str = ft_substr(input, begin, len);
				// printf("input_to_token:: tk_str: %s, %p\n", tk_str,tk_str);
				ft_lstadd_back(tk_head, ft_lstnew(tk_str, global_env->path_tab, envp)); //add at the end of the list. lst new adds a new element to the list.
				// free(tk_str);
				begin = i; // = 3
			}
		}
		i++;
	}
	len = i - begin;
	// printf("%d: begin:%d len:%d\n", i, begin, len);
	// printf("BEFORE substr ->input_to_token:: tk_str: %s, %p\n", tk_str,tk_str);
	tk_str = ft_substr(input, begin, len);
	// printf("input_to_token:: tk_str: %s, %p\n", tk_str,tk_str);
	ft_lstadd_back(tk_head, ft_lstnew(tk_str, global_env->path_tab, envp));
	// print_lst(*tk_head);
	return (0);
	// check errors in addback | lstnew, substr for malloc if NULL, it is not handled anywhere yet. 
}

// TEST Minishell
// < "file entree.txt" wc -l ||         ls  -l << 'output de sortie'
