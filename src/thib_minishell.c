/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/09/01 01:13:53 by thibault         ###   ########.fr       */
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
		// print_lst(tk_head);
		parse_token(&tk_head);
		execution(&tk_head);
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
