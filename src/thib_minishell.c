/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfinocie <vfinocie@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/09/17 15:57:22 by vfinocie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pour les leaks, checkez "Instruments" a l'ecole il est sur les macs. Ca permet de lancer la commande leaks pendant que minishell tourne pour checker les leaks beaucoup plus facilement. Je vous montre si vous voulez.

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tk	*tk_head;
	int		*delimiter_tab;
	char	**path;
	(void)argc;
	(void)argv;
	

	tk_head = NULL;
	delimiter_tab = NULL;
	path = get_path(envp);
	
	//envp can be sent empty into the program, check if empty before continuing to avoid wrong dereference (segfault)
	// tip : there is a bash command that you can run your program with in order to empty the envp that it receives. 
	// tip : when you run bash with this command, bash still add default env variables in the empty env. So you can do the same here, 
	
	// when receiving and empty env, to avoid segfault, add what you judge necessary and logic according to bash
	// printf("path adress:%p\n", path);
	// print_strtab(path);
	while (1)
	{
		 // Sauvegarder les descripteurs de fichier originaux
		 // A SUPPRIMER PAR LA SUITE
		int original_stdin = dup(STDIN_FILENO);
		int original_stdout = dup(STDOUT_FILENO);
		
		
		input = readline("minishell> ");

		if (check_input(input)) // return 1 means something is wrong. 
		{
			if (input != NULL)
				free(input);
			continue; // skip the current iteration, and starts a new one, in this case, goes back to reading the input with readline()
		}
		// get_delimiter(input);
		delimiter_tab = get_delimiter(input);  // This array of ints the size of the input, will be used to mark whether each character in the input is a delimiter (1) or not (0).

		// if delimiter_tab is NULL, sending it in input_to_token might not be safe.
		input_to_token(input, path, &tk_head, delimiter_tab);
		// here we have a linked list, with each node is a part of the input seperated with the delimiter, that was set in the delimiter array of int.
		
		// if ft_calloc called in get_delimiter, return NULL (shit happens), you can't free it, you'll have a memory problem. 
		free(delimiter_tab);
		parse_token(&tk_head);
		print_lst(tk_head);
		set_redirection(&tk_head);


		// Rétablir les descripteurs de fichier
		// A SUPPRIMER PAR LA SUITE
		dup2(original_stdin, STDIN_FILENO);
   	 	dup2(original_stdout, STDOUT_FILENO);

		// Fermer les descripteurs de fichier sauvegardés et redirigés
		// A SUPPRIMER PAR LA SUITE
		close(original_stdin);
		close(original_stdout);
	
		// execution(&tk_head);

		// printf("Vous avez entré : %s\n", input);
		// if (is_redir_in(input, 0))
		// 	printf("is < \n");
		free(input);
		
	}
	free_strtab(path); //ne pas free dans la boucle while
	return(0);
}

char	**get_path(char **envp)
{
	char	**path;
	int		i;

	path = NULL;
	i = 0;
	
	// run minishell with NULL envp, might have a segfault here with the dereferencement.
	// proposition : while (envp && envp[i] != 0)
	
	while (envp[i] != 0)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			break;
		i++;
	}
	path = ft_split(envp[i], ':');
	// printf("IN SPLIT: path adress:%p\n", path);
	return (path);
}


int	check_input(char *input)
{
	if (input == NULL)
		return(1);
	if (*input == 0)
		return (1);
	return (0);
}
