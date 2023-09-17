/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/09/17 12:54:22 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// printf("path adress:%p\n", path);
	// print_strtab(path);
	while (1)
	{
		 // Sauvegarder les descripteurs de fichier originaux
		 // A SUPPRIMER PAR LA SUITE
		int original_stdin = dup(STDIN_FILENO);
		int original_stdout = dup(STDOUT_FILENO);
		
		
		input = readline("minishell> ");

		if (check_input(input))
		{
			if (input != NULL)
				free(input);
			continue;
		}
		// get_delimiter(input);
		delimiter_tab = get_delimiter(input);
		input_to_token(input, path, &tk_head, delimiter_tab);
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
