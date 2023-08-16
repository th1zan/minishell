/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/08/16 10:12:28 by thibault         ###   ########.fr       */
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
		printf("input[%d]:%c ", i, input[i]);
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
				if (input[i] == 0)
					{
						//gestion erreur, quote non fermée
						return (NULL);
					}	
				i++;
			}
		}	
		else if (is_whitespace(input[i]))
		{
			delimiter[i] = 1;
			i++;
			while (!is_whitespace(input, i))
			{	
				if (input[i] == 0)
					{
						//gestion erreur, quote non fermée
						return (NULL);
					}	
				i++;
			}
		}
		else if (is_word(input[i]))
		{
			delimiter[i] = 1;
			i++;
			while (is_word(input, i))
			{	
				if (input[i] == 0)
					{
						//gestion erreur, quote non fermée
						return (NULL);
					}	
				i++;
			}
		}				
		else
		{
			delimiter[i] = 0;
		}
		// PRINT TEST
		if (input[i])
			printf("delimiter[%d]:%d\n", i, delimiter[i]);
		i++;
	}
	

	// PRINT TEST
	printf("%s\n", input);
	i = 0;
	while (i < (int)ft_strlen(input))
	{
		printf("%d", delimiter[i]);
		i++;
	}
	printf("\n---------------------\n\ns");

	return (delimiter);
}


// int	*get_delimiter(char *input)
// {
// 	int		i;
// 	int		*delimiter;

// 	delimiter = (int *)ft_calloc(ft_strlen(input), sizeof(int) + 1);
// 	if (!delimiter)
// 	{
// 		//Gestion d'erreur
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (input[i] != 0)
// 	{
// 		// printf("input[%d]:%c ", i, input[i]);
// 		if (is_twochar_delim(input, i) && input[i + 1])
// 		{
// 			delimiter[i] = 1;
// 			i = i + 2;
// 			if (input[i])
// 				delimiter[i] = 1;
// 		}
// 		else if (is_onechar_delim(input, i))
// 		{
	
// 			delimiter[i] = 1;
// 			i = i + 1;
// 			if (input[i])
// 				delimiter[i] = 1;
// 		}
// 		else
// 		{
// 			delimiter[i] = 0;
// 		}
// 		//PRINT TEST
// 		// if (input[i])
// 		// 	printf("delimiter[%d]:%d\n", i, delimiter[i]);
// 		i++;
// 	}
	

// 	//PRINT TEST
// 	// printf("%s\n", input);
// 	// i = 0;
// 	// while (i < (int)ft_strlen(input))
// 	// {
// 	// 	printf("%d", delimiter[i]);
// 	// 	i++;
// 	// }
// 	// printf("\n---------------------\n\ns");

// 	return (delimiter);
// }

int	input_to_token(char *input, t_tk **tk_head, int *delimiter)
{
	int		begin; //delimiter: tab[0] = begin, tab[1] = end
	int		i;
	int		len;
	char	*tk_str;

	*tk_head = ft_lstnew(input);
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
			tk_str = ft_substr(input, begin, len);
			ft_lstadd_back(tk_head, ft_lstnew(tk_str));
			begin = i;
		}
		i++;
	}
	len = i - begin;
	// printf("%d: begin:%d len:%d\n", i, begin, len);
	tk_str = ft_substr(input, begin, len);
	ft_lstadd_back(tk_head, ft_lstnew(tk_str));
	*tk_head = ft_lst_remove(*tk_head);
	
	// print_lst(*tk_head);
	return (0);
}

/*
int	*get_delimiter(char *input)
{
	int		i;
	int	*delimiter;

	printf("%s\n", input);
	delimiter = (int *)ft_calloc(ft_strlen(input), sizeof(int) + 1);
	i = 0;
	while (input[i] != 0)
	{
		printf("input[%d]:%c ", i, input[i]);
		if (i != 0 && is_onechar_delim(input, i - 1) && !is_quoted_char(input, i) && is_onechar_delim(input, i))
			delimiter[i] = 1;
		else if (i != 0 && is_onechar_delim(input, i - 1) && is_onechar_delim(input, i))
			delimiter[i] = 1;
		else if ((input[i] == '\\' || input[i] == '\'' || input[i] == '"') && !is_quoted_char(input, i))
		{
			if(i != 0 && !is_quote(input, i - 1) && !is_quote(input, i + 1))
				delimiter[i] = 1;
		}
		else if ((input[i] == '$' || input[i] == '`') && !is_quoted_char(input, i))
			delimiter[i] = 1;
		else if (!is_quoted_char(input, i) && !is_onechar_delim(input, i))
			delimiter[i] = 1;
		else if (input[i] == '\n' && !is_quoted_char(input, i))
			delimiter[i] = 1;
		else if (is_whitespace(input[i]) && !is_quoted_char(input, i))
			delimiter[i - 1] = 1;
		else if (input[i] == '#')
		{
			delimiter[i] = 1;
			while (input[i] != '\n')
				i++;
			delimiter[i] = 1;
		}
		else
			delimiter[i] = 0;
		printf("delimiter[%d]:%d\n", i, delimiter[i]);
		i++;
	}

	// PRINT TEST
	printf("%s\n", input);
	i = 0;
	while (i < (int)ft_strlen(input))
	{
		printf("%d", delimiter[i]);
		i++;
	}
	printf("---------------------\n\ns");

	
		// 1. input[i] == '\0'
		// 2. input[i - 1] == operator && input [i] != quote && input[i] == (part of)operator 
		// 3. input[i - 1] == operator && input[i] != (part of) operator
		// 4. input[i] ==  \, ', or " && input[i] not quoted -> input[i -1] != quote && input[i + 1] != quote
		// 	4.b Find end quote to find the next delimiter ?
		// 	4.c quoting rule
		// 5. (input[i] == $ || input[i] == `) && input[i] NOT quoted
		// 	5b. identify start for 1.Parameter Expansion 2.Command substitution 3.Arithmetic Expansion
		// 		The start is when input[i] == '$' or "${", "$(" or '`', and "$((" && input[i] not quoted
		// 	5c. identify end.
		// 	5d. If new quotes or param extension, etc are found -> process them recursively
		// 6. input[i] NOT quoted && input[i] == operator (begin of) -> operator (== delimiter)
		// 7. input[i] == <newline> && NOT quoted
		// 8. input[i] == <blank> && NOT quoted => input[i - 1] is a delimiter and input[i] -> discarded
		// 9. input[i -1] is WORD => input[i] is WORD . 
		// 10.  input[i] == # => is a comment => delimiter. Next delimiter is <newline>
		// 11. input[i] = start of new word	
	
	return (delimiter);
}
*/

/*
int	input_to_token(char *input, t_tk **tk_head)
{
	int		tab[2]; //delimiter: tab[0] = begin, tab[1] = end
	int		i;
	int		len;
	char	*tk_str;

	*tk_head = ft_lstnew(input);
	tab[0] = 0;
	tab[1] = 0;
	len = 0;

	i = 0;
	while (input[i] != 0)
	{
		// printf("%d: %c\n", i, input[i]);
		
		// check first "two character delimiter"
		if (is_twochar_delim(input, i))
		{
			//extraire le texte situé avant le delimiter
			len = (i - 1) - tab[0];
			if (!is_whitespace(input[i - 1]))
				len = len + 1;
			tk_str = ft_substr(input, tab[0], len);
			ft_lstadd_back(tk_head, ft_lstnew(tk_str));

			//extraire le delimiter
			len = 2;
			tk_str = ft_substr(input, i, len);
			ft_lstadd_back(tk_head, ft_lstnew(tk_str));
			i = i + 2;
			tab[0] = i;
		}// then check "one character delimiter"
		else if (is_onechar_delim(input, i))
		{
			//extraire le texte situé avant le delimiter
			len = (i - 1) - tab[0];
			if (!is_whitespace(input[i - 1]))
				len = len + 1;
			tk_str = ft_substr(input, tab[0], len);
			ft_lstadd_back(tk_head, ft_lstnew(tk_str));
			
			//extraire le delimiter
			len = 1;
			tk_str = ft_substr(input, i, len);
			ft_lstadd_back(tk_head, ft_lstnew(tk_str));
			i = i + 1;
			tab[0] = i;
		}// then check "end character delimiter"
		else if (input[i + 1] == '\0')
		{
			//extraire le texte situé avant le delimiter
			len = i + 1 - tab[0];
			tk_str = ft_substr(input, tab[0], len);
			ft_lstadd_back(tk_head, ft_lstnew(tk_str));
			i++;
		}
		else
		{
			i++;
			tab[1] = i;
		}
	}
	*tk_head = ft_lst_remove(*tk_head);
	
	// print_lst(*tk_head);
	return (0);
}

*/


/*

			Non utilisé: Opérateurs de Groupement : () {}


	        Si (caractere est un opérateur)
			-> Opérateurs de Redirection : > >> <  2> |
			OU Opérateurs de Contrôle : ; & && ||
			OU Début d'un Here-Document : <<
				AjouterTokenAListe(caractere comme opérateur);
	
			Sinon Si (backslash, apostrophe simple ou double)
		        position = TraiterQuoting(ligne, position);
	
	        Sinon Si (caractere est '$' ou '`') -> Opérateurs de Substitution : `...` $(...) ${...}
	            position = TraiterExpansion(ligne, position);
	            
	        Sinon Si (caractere est un nouvel opérateur)
	            DelimiterTokenActuel();
	            AjouterTokenAListe(caractere comme nouvel opérateur);
	        
	        Sinon Si (caractere est <newline>)
	            DelimiterTokenActuel();
	            
	        Sinon Si (caractere est <blank>)
	            DelimiterTokenActuel();
	            IgnorerCaractere();
	            
	        Sinon Si (caractere est '#')
	            IgnorerJusquaNewline();
	        
	        Sinon
	            AjouterCaractereAuTokenActuel(caractere);*/