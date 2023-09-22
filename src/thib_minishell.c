/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/09/22 10:33:35 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pour les leaks, checkez "Instruments" a l'ecole il est sur les macs. Ca permet de lancer la commande leaks pendant que minishell tourne pour checker les leaks beaucoup plus facilement. Je vous montre si vous voulez.

#include "minishell.h"

// < IN_file grep a | wc -l > OUT_file

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tk	*tk_head;
	int		*delimiter_tab;
	char	**path;
	int	original_std[3];
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
	
		save_std(original_std);
		
		input = get_line();

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
		if (check_parsing(tk_head) == 0)
		{
			set_redirection(&tk_head);
			// print_lst(tk_head);
			execution(&tk_head);
			// close_all_fd(&tk_head);
			restore_std(original_std);
		}
		printf("input: %s\n", input);
		free(input);
		
	}
	free_strtab(path); //ne pas free dans la boucle while
	return(0);
}

//fonction à comprendre et commenter
char	*get_line(void)
{
	struct termios	saved;
	struct termios	attributes;
	char			*line;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	line = readline("minishell> ");
	if (check_input(line))
		return (NULL);
	// create_history(line);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	return (line);
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
