/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/08/11 16:08:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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