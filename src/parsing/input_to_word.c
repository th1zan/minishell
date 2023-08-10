/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:58:05 by thibault          #+#    #+#             */
/*   Updated: 2023/08/10 10:42:53 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	input_to_word(char *input)
{

	printf("input%s\n", input);
	return(0);
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