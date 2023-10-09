/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:31:29 by thibault          #+#    #+#             */
/*   Updated: 2023/10/09 17:27:53 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	del_whitespace(char **str)
{
	int		begin;
	int		end;
	int		len;
	char	*temp;

	//for (int i = 0; str[i]; i++) {
	//	printf("str[%d] : %s\n", i, str[i]);
	//}

	if (!*str || **str == '\0')
		return (0);
	begin = 0;
	while(str[begin])
	{
		if (!str[begin])
			break;
		return(0);
	}
	begin = 0;
	while (is_whitespace((*str)[begin]))
		begin++;
	end = ft_strlen(*str) -1;
	while(is_whitespace((*str)[end]))
		end--;
	len = end - begin + 1;
	temp = *str;
	*str = ft_substr(temp, begin, len);
	free(temp);
	return (0);
}

char *get_var_name_from_input(char *input, int *i)
{
	int		end = 0;
	(*i)++;
	while (is_portable_filename_char(input[*i + end]) == 1)
		end++;
	return ft_substr(input, *i, end);
}

int get_var_name_len_from_input(char *input, int i)
{
	int		len = 0;

	while (is_portable_filename_char(input[i + len]) == 1)// || input[i + len] == '?')
		len++;
	len++;
	return (len);
}

char *find_value_in_tab(char *var_name, char **var_values_tab)
{
	int i = 0;
	while(var_values_tab[i])
	{
		if (ft_strncmp(var_name, var_values_tab[i], ft_strlen(var_name)) == 0)
			return (var_values_tab[i]);
		i++;
	}
	return (NULL);
}

char *get_value_after_equal(char *var_value)
{
	int i = 0;
	while (var_value && var_value[i] != '=') { i++; }
	i++;
	return ft_substr(var_value, i, ft_strlen(var_value) - i);
}

char *replace_var_in_string(char *input_str, int *i, char **var_values_tab)
{
	char	*tmp;
	char	*var_value;
	int		start;
	int		var_name_len;

	printf("BEGIN of fct: replace_var_in_string\n");
	start = *i; // Sauvegardez la position actuelle
	var_value = get_var_value(input_str, i, var_values_tab);
	if (!var_value)
		var_value = ft_strdup(" ");  // Si la variable n'est pas trouvée, utilisez une chaîne vide
	printf("i: %d, var_value: %s\n", *i, var_value);
	var_name_len = get_var_name_len_from_input(input_str, *i); // Calculez la longueur du nom de la variable
	tmp = ft_substr(input_str, 0, start); // Prenez la partie de la chaîne avant le nom de la variable
	char *tmp2 = ft_strjoin(tmp, var_value); // Concaténez la valeur de la variable
	printf("tmp: %s, tmp2: %s\n", tmp, tmp2);
	free(tmp);
	free(var_value);
	char *result = ft_strjoin(tmp2, &input_str[start + var_name_len]); // Concaténez la partie restante de la chaîne après le nom de la variable
	printf("result: %s, inputstr: %c\n", result, input_str[start + var_name_len]);
	free(tmp2);
	printf("END of fct: replace_var_in_string\n");
	return (result);
}

int	replace_with_values(char **input, char ***var_values_tab)
{
	int		i;
	char	*input_str;
	char	*new_input;

	input_str = *input;
	i = 0;

	while (input_str[i])
	{
		if (input_str[i] == '$' && check_inside_simple_quote(input_str, i) != SUCCESS)
		{
			if (ft_strncmp(&input_str[i], "$?=", 3))
			{
				new_input = ft_itoa(global_env->status);
			}
			else
				new_input = replace_var_in_string(input_str, &i, *var_values_tab);
			if (input_str != new_input)  // Vérifiez si input_str et new_input sont différents avant de libérer
			{
				free(input_str);
				input_str = new_input;
			}
		}
		else
		{
			i++;
		}
	}
	
	*input = input_str;  // Pas besoin de vérifier si new_input est non NULL car input_str pointera toujours vers la dernière version de la chaîne
	
	return (0);
}




char *get_var_value(char *input, int *i, char **var_values_tab)
{
	char	*var_name;
	char	*var_value_tab;
	char	*var_value;

	var_name = get_var_name_from_input(input, i);
	var_value_tab = find_value_in_tab(var_name, var_values_tab);
	if (var_value_tab)
		var_value = get_value_after_equal(var_value_tab);
	else
		var_value = NULL;
	if (!var_value)
		var_value = ft_strdup(" ");
	free(var_name);
	return (var_value);
}

// int	replace_env_variables(char **input, char **env)
// {
// 	// char	**var_values_tab;

// 	// var_values_tab = NULL;
// 	// printf("input: %s env[0]:%s\n", *input, env[0]);
// 	// var_values_tab = get_variables_values(*input);
// 	replace_with_values(input, env);
// 	// print_strtab(env);
// 	// free (input);
// 	// *input = tmp_input;
// 	return (0);
// }

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
