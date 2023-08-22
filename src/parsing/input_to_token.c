/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/08/22 16:54:37 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*get_delimiter(char *input)
{
	int		i;
	int		*delimiter;

	delimiter = (int *)ft_calloc(ft_strlen(input), sizeof(int) + 1);
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
		if (is_twochar_delim(input, i) && input[i + 1])
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
						//gestion erreur, quote non fermée
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
						//gestion erreur, quote non fermée
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
						//gestion erreur, quote non fermée
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
		else if (is_name(input[i]))
		{
			delimiter[i] = 1;
			i++;
			while (is_portable_filename_char(input[i]))
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
		i++;
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

int	input_to_token(char *input, t_tk **tk_head, int *delimiter)
{
	int		begin; //delimiter: tab[0] = begin, tab[1] = end
	int		i;
	int		len;
	char	*tk_str;

	*tk_head = NULL;
	begin = 0;
	len = 0;

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
				tk_str = ft_substr(input, begin, len);
				ft_lstadd_back(tk_head, ft_lstnew(tk_str));
				begin = i;
			}
		}
		i++;
	}
	len = i - begin;
	// printf("%d: begin:%d len:%d\n", i, begin, len);
	tk_str = ft_substr(input, begin, len);
	ft_lstadd_back(tk_head, ft_lstnew(tk_str));
	// print_lst(*tk_head);
	return (0);
}

// TEST Minishell
// < "file entree.txt" wc -l ||         ls  -l << 'output de sortie'
