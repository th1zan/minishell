/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thib_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/10/02 15:51:52 by thibault         ###   ########.fr       */
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
		
		input = get_line("minishell> ");

		if (check_input(input)) // return 1 means something is wrong. 
		{
			if (input != NULL)
				free(input);
			continue; // skip the current iteration, and starts a new one, in this case, goes back to reading the input with readline()
		}
		replace_env_variables(&input);
		fprintf(stderr, "===INFO===: New input with variable's content\n");
		printf("%s\n", input);

		delimiter_tab = get_delimiter(input);  // This array of ints the size of the input, will be used to mark whether each character in the input is a delimiter (1) or not (0).

		// if delimiter_tab is NULL, sending it in input_to_token might not be safe.
		input_to_token(input, path, &tk_head, delimiter_tab);
		// here we have a linked list, with each node is a part of the input seperated with the delimiter, that was set in the delimiter array of int.
		
		// if ft_calloc called in get_delimiter, return NULL (shit happens), you can't free it, you'll have a memory problem. 
		free(delimiter_tab);
		parse_token(&tk_head);
		fprintf(stderr, "===INFO===: end of parsing\n");
		fprintf(stderr, "===INFO===: print TK list::\n");
		// print_lst(tk_head);
		// if (check_parsing(tk_head) == 0)
		{
			fprintf(stderr, "===INFO===: end of parsing check\n");
			set_redirection(&tk_head);
			fprintf(stderr, "===INFO===: end of redirection\n");
			// fprintf(stderr, "===INFO===: print TK list::\n");
			// print_lst(tk_head);
			fprintf(stderr, "===INFO===: result of cmd line (if displayed)::\n");
			execution(&tk_head);
			fprintf(stderr, "===INFO===: end of execution\n");
			// print_lst(tk_head);
			restore_std(original_std);
		}
		fprintf(stderr, "===INFO===: initial input:: %s\n", input);
		free(input);
		
	}
	free_strtab(path); //ne pas free dans la boucle while
	return(0);
}

char	*get_line(char *prompt)
{
	struct termios	saved;         // Structure pour sauvegarder les attributs actuels du terminal.
	struct termios	attributes;    // Structure pour définir de nouveaux attributs pour le terminal.
	char			*line;

	tcgetattr(STDIN_FILENO, &saved);  // Obtenir et sauvegarder les attributs actuels du terminal.
	tcgetattr(STDIN_FILENO, &attributes);  // Obtenir les attributs actuels du terminal pour les modifier.

	attributes.c_lflag &= ~ECHOCTL;  // Modifier les attributs pour désactiver l'affichage des caractères de contrôle. Ex: le caractère de contrôle Ctrl-C ne sera pas affiché comme "^C"
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);  // Définir les nouveaux attributs pour le terminal.

	line = readline(prompt);  // Lire une ligne de l'utilisateur en utilisant le prompt fourni.

	if (check_input(line))    // Vérifier l'entrée de l'utilisateur (la fonction check_input n'est pas fournie, donc je ne peux pas dire exactement ce qu'elle fait).
		return (NULL);

	// create_history(line);  // (Commenté) Ajouter la ligne à l'historique.

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);  // Restaurer les attributs originaux du terminal.

	return (line);  // Renvoyer la ligne lue.
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

int	save_std(int *original_std)
{
	original_std[0] = dup(STDIN_FILENO);
	original_std[1] = dup(STDOUT_FILENO);
	original_std[2] = dup(STDERR_FILENO);
	if (original_std[0] == -1 || original_std[1] == -1 || original_std[2] == -1)
	{
		perror("dup error: original_std[0] in save_std");
		fprintf(stderr, "errno: %d\n", errno);
		return (-1);
	}
	return 0;
}

int	restore_std(int *original_std)
{
	if (dup2(original_std[0], STDIN_FILENO) == -1)
	{
		perror("dup2 error: original_std[0] in restore_std");
		fprintf(stderr, "original_std[0]: %d, errno: %d\n", original_std[0], errno);
		return (-1);
	}	
	if (dup2(original_std[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 error: original_std[1] in restore_std");
		fprintf(stderr, "original_std[1]: %d, errno: %d\n", original_std[1], errno);
		return (-1);
	}	
	if (dup2(original_std[2], STDERR_FILENO) == -1)
	{
		perror("dup2 error: original_std[2] in restore_std");
		fprintf(stderr, "original_std[2]: %d, errno: %d\n", original_std[2], errno);
		return (-1);
	}
	close(original_std[0]);
	close(original_std[1]);
	close(original_std[2]);
	return 0;
}

int	count_variables(char *input)
{
	int count = 0;
	int i = 0;

	while (input[i])
	{
		if (input[i] == '$' && check_inside_simple_quote(input, i) != SUCCESS)
		{
			count++;
			i++;
			while (is_portable_filename_char(input[i]) && input[i] != 0)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**get_variables_values(char *input)
{
	int n_variables;
	char **var_values_tab;;
	int i;
	int j;
	int start;

	n_variables = count_variables(input);
	var_values_tab = (char **)malloc((n_variables + 1) * sizeof(char *));
	if (!var_values_tab)
		return(NULL);
	i = 0;
	j = 0;
	start = 0;
	while (input[i] && j < n_variables)
	{
		if (input[i] == '$' && check_inside_simple_quote(input, i) != SUCCESS)
		{
			start = i;
			i++;
			while (is_portable_filename_char(input[i]) && input[i] != 0)
				i++;
			char *variable_name = ft_substr(input, start + 1, i - start - 1);
			// var_values_tab[j] = get_env_variable(variable_name);
			var_values_tab[j] = ft_strdup("VALEUR_VARIABLE"); 
			free(variable_name);
			j++;
		}
		else
			i++;
	}
	var_values_tab[j] = NULL;
	return (var_values_tab);
}

int	replace_with_values(char **input, char **var_values_tab)
{
	char *new_input;
	char *tmp;
	char *tmp2; 
	int i;
	int j;
	int start;
	char *input_str;

	input_str = *input;
	new_input = ft_strdup("");
	i = 0;
	j = 0;
	start = 0;
	while (input_str[i] && var_values_tab[j])
	{
		if (input_str[i] == '$' && check_inside_simple_quote(input_str, i) != SUCCESS)
		{
			tmp = ft_substr(input_str, start, i - start);
			tmp2 = ft_strjoin(tmp, new_input);
			free(new_input);
			new_input = ft_strjoin(tmp2, var_values_tab[j]);
			free(tmp2);
			free(tmp);
			i++;
			while (is_portable_filename_char(input_str[i]))
			{	
				i++;
			}
			start = start + i;
			j++;
		}
		else
			i++;
	}
	tmp = ft_strjoin(new_input, &input_str[i]);
	free(new_input);
	free(input_str);
	*input = tmp;
	// printf("new_input FINAL: %s\n", new_input);
	return (0);
}

int	replace_env_variables(char **input)
{
	char	**var_values_tab;
	int		i;

	var_values_tab = get_variables_values(*input);
	replace_with_values(input, var_values_tab);
	// free (input);
	// *input = tmp_input;
	i = 0;
	while (var_values_tab[i])
		free(var_values_tab[i++]);
	free(var_values_tab);
	return (0);
}

int	check_inside_simple_quote(char *input, int index)
{
	int i = 0;
	int in_quote = 0;

	while (i < index && input[i])
	{
		if (input[i] == '\'')
		{
			if (in_quote)
				in_quote = 0; // Si nous sommes déjà à l'intérieur d'une citation, cela signifie que nous avons trouvé la fin de la citation
			else
				in_quote = 1; // Sinon, cela signifie que nous avons trouvé le début d'une citation
		}
		i++;
	}

	if (in_quote)
		return (SUCCESS); // Le caractère à l'index donné est à l'intérieur de guillemets simples
	else
		return (FAILURE); // Le caractère à l'index donné n'est pas à l'intérieur de guillemets simples
}
