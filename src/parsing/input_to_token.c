/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/10/10 15:33:21 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
delimiter tab:  tab of int
lenght of delimiter tab: length of input string
if tab[i] == 1 -> input[i] == delimiter
Then 


*/

int	*get_delimiter(char *input) //input = user's command not parsed / input = "test"
{
	int		i;
	int		*delimiter;

	delimiter = (int *)ft_calloc(ft_strlen(input), sizeof(int) + 1); // size = ft_strlen(input) && count = sizeof(int) + 1 | size = 4 + 1 ('\0'), count = 4. Isn't it (the number of elements + 1) times sizeof() ?
	if (!delimiter)
	{
		//Gestion d'erreur
		return (NULL);
	}
	i = 0;
	while (i < (int)ft_strlen(input))
	{
		// PRINT TEST
		// printf("input[%d]:%c ", i, input[i]);
		if (is_twochar_delim(input, i) && input[i + 1]) // check for input[i + 1] != NULL already done in is_twochar_delim(), if it is NULL, the first condition is not met anyway.
		{
			delimiter[i] = 1;
			i++;
		}
		else if (is_onechar_delim(input, i))
		{
			delimiter[i] = 1;
		}
		else if (is_simple_quote(input, i))
		{
	
			delimiter[i] = 1;
			i++;
			while (!is_simple_quote(input, i))
			{	
				if (input[i] == 0)
					{
						printf("minishell: error: unclosed quote\n");
						return (NULL);
					}	
				i++;
			}
		}
		else if (is_double_quote(input, i))
		{
			delimiter[i] = 1;
			i++;
			while (!is_double_quote(input, i))
			{	
				if (input[i] == 0)
					{
						printf("minishell: error: unclosed double quote\n");
						return (NULL);
					}	
				i++;
			}
		}
		else if (is_back_quote(input, i))
		{
	
			delimiter[i] = 1;
			i++;
			while (!is_back_quote(input, i))
			{	
				if (input[i] == 0)
					{
						printf("minishell: error: unclosed back quote\n");
						return (NULL);
					}	
				i++;
			}
		}
		else if (input[i] == '\n')
		{
			delimiter[i] = 1;
			i++;
			while (input[i] == '\n')
			{	
				i++;
			}
			i--;
		}	
		else if (is_whitespace(input[i]))
		{
			delimiter[i] = 1;
			i++;
			while (is_whitespace(input[i]))
			{	
				i++;
			}
			i--;
		}
		else if (is_name(input[i]) || input[i] == '/' || input[i] == '$')
		{
			delimiter[i] = 1;
			i++;
			while (is_portable_filename_char(input[i]) || input[i] == '/') 
			{	
				i++;
			}
			i--;
		}		
		else
		{
			delimiter[i] = 0;
		}
		// PRINT TEST
		// if (input[i])
		// 	printf("input[%d]:%c is delimiter[%d]:%d \n", i, input[i], i, delimiter[i]);
		i++; // if the first if is true,, i++ was already done, so this new i++ might go too far. 
	}

	// PRINT TEST
	// printf("\n%s\n", input);
	// i = 0;
	// while (i < (int)ft_strlen(input))
	// {
	// 	printf("%d", delimiter[i]);
	// 	i++;
	// }
	// printf("\n---------------------\n\ns");

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
	char	**path;

	*tk_head = NULL;
	begin = 0;
	len = 0;

	path = get_path(*envp);
	// print_strtab(path);
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
				ft_lstadd_back(tk_head, ft_lstnew(tk_str, path, envp)); //add at the end of the list. lst new adds a new element to the list.
				begin = i; // = 3
			}
		}
		i++;
	}
	len = i - begin;
	// printf("%d: begin:%d len:%d\n", i, begin, len);
	tk_str = ft_substr(input, begin, len);
	ft_lstadd_back(tk_head, ft_lstnew(tk_str, path, envp));
	// print_lst(*tk_head);
	return (0);
	// check errors in addback | lstnew, substr for malloc if NULL, it is not handled anywhere yet. 
}

// TEST Minishell
// < "file entree.txt" wc -l ||         ls  -l << 'output de sortie'
