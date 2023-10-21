/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OLD_input_to_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/10/17 22:40:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	input_to_word(char *input)
// {
// 	int		tab[2]; //tab[0] = begin, tab[1] = end of word
// 	int		i;
// 	int		nb_word;
// 	char	**tab_words;

// 	i = 0;
// 	tab[0] = 0;
// 	tab[1] = 0;
// 	/*Count input nb words*/
// 	nb_word = count_words(input);
// 	tab_words = NULL;
// 	if (malloc_strtab(&tab_words, nb_word))
// 		{
// 			perror ("erreur allocation tab_words\n");
// 			exit (0);
// 		}

// 	//BLOC TEST
// 	// printf("tab_words: %p, nb words = %d\n", tab_words, nb_word);
// 	// for (int j = 0; j < nb_word; j++)
//    	//  tab_words[j] = strdup("test"); 
// 	// print_strtab(tab_words);

// 	/*Find delimiters and extract word*/
// 	nb_word = 0;
// 	while (input[i] != 0)
// 	{
// 		tab[0] = tab[1];
// 		while (input[i] != 0)
// 		{
// 			// check first "two character delimiter"
// 			if (is_twochar_delim(input, i))
// 			{
// 				tab[1] = i;
// 				tab_words[nb_word++] = ft_substr(input, tab[0], tab[1] - tab[0]);
// 				tab_words[nb_word++] = ft_substr(input, i, 2);
// 				i = i + 2;
// 				tab[0] = i;
// 				break;
// 			}// then check "one character delimiter"
// 			else if (is_onechar_delim(input, i))
// 			{
// 				tab[1] = i;
// 				tab_words[nb_word++] = ft_substr(input, tab[0], tab[1] - tab[0]);
// 				tab_words[nb_word++] = ft_substr(input, i, 1);;
// 				i++;
// 				tab[0] = i;
// 				break;
// 			}
// 			else if (input[i + 1] == 0)
// 			{
// 				tab[1] = i + 1;
// 				break;
// 			}
// 			printf("input[%d]:%c tab[0]:%d tab[1]:%d i:%d nb_word:%d\n", i, input[i], tab[0], tab[1], i, nb_word);
// 			i++;
// 		}
// 		/*Copy substr in tab_word*/
// 		// tab_words[nb_word] = ft_substr("okaaay", 0, 6);
// 		if (tab[1] > tab[0])
// 			tab_words[nb_word++] = ft_substr(input, tab[0], tab[1] - tab[0]);
// 		// printf("input[%d]:%c tab[0]:%d tab[1]:%d i:%d nb_word:%d\n", i, input[i], tab[0], tab[1], i, nb_word);
// 		// tab_words[nb_word] = ft_strdup("okaaay");
// 	}
// 	print_strtab(tab_words);


	
// 	return (0);

// }

int	input_to_word(char *input)
{
	int		tab[2]; //tab[0] = begin, tab[1] = end of word
	int		i;
	int		nb_word;
	char	**tab_words;

	i = 0;
	tab[0] = 0;
	tab[1] = 0;
	/*Count input nb words*/
	nb_word = count_words(input);
	tab_words = NULL;
	if (malloc_strtab(&tab_words, nb_word))
	{
		perror("erreur allocation tab_words\n");
		exit(0);
	}

	nb_word = 0;
	while (input[i] != 0)
	{
		// check first "two character delimiter"
		if (is_twochar_delim(input, i))
		{
			if (i > tab[0]) // Check if there's a word before the delimiter
				tab_words[nb_word++] = ft_substr(input, tab[0], i - tab[0]);
			tab_words[nb_word++] = ft_substr(input, i, 2);
			i += 2;
			tab[0] = i;
		}
		// then check "one character delimiter"
		else if (is_onechar_delim(input, i))
		{
			if (i > tab[0]) // Check if there's a word before the delimiter
				tab_words[nb_word++] = ft_substr(input, tab[0], i - tab[0]);
			tab_words[nb_word++] = ft_substr(input, i, 1);
			i++;
			tab[0] = i;
		}
		else
		{
			i++;
		}
	}
	// Add the last word if there's any
	if (i > tab[0])
		tab_words[nb_word++] = ft_substr(input, tab[0], i - tab[0]);
		

	print_strtab(tab_words);
	return (0);
}


int	count_words(char *input)
{
	int	i;
	int nb_words;

	i = 0;
	nb_words = 1;
	while (input[i] != 0)
	{
		// check first "two character delimiter"
		if (is_twochar_delim(input, i))
		{
			nb_words = nb_words + 2;
			i++;
		}// then check "one character delimiter"
		else if (is_onechar_delim(input, i))
		{
			nb_words = nb_words + 2;
		}
		i++;
		// printf("%d: %c :%d\n", i, input[i], nb_words);
	}
	return (nb_words);
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