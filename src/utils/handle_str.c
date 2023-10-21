/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:31:29 by thibault          #+#    #+#             */
/*   Updated: 2023/10/20 14:42:49 by thibault         ###   ########.fr       */
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



char	*replace_var_in_string(char *input_str, int *i, char **var_values_tab)
{
	char	*tmp;
	char	*var_value;
	char	*tmp2;
	char	*result;
	int		start;
	int		var_name_len;

	start = *i;
	var_value = get_var_value(input_str, i, var_values_tab);
	if (!var_value)
		var_value = ft_strdup("");
	var_name_len = get_var_name_len_from_input(input_str, *i);
	tmp = ft_substr(input_str, 0, start);
	tmp2 = ft_strjoin(tmp, var_value);
	free(tmp);
	free(var_value);
	result = ft_strjoin(tmp2, &input_str[start + var_name_len]);
	free(tmp2);
	return (result);
}


char	*replace_var_status_in_string(char *input_str, int *i, char *var_value)
{
	char	*tmp;
	char	*tmp2;
	char	*result;
	int		start;
	int		var_name_len;

	start = *i;

	// Calculer la longueur du nom de la variable dans la chaîne d'entrée.
	// Cette fonction doit être définie pour calculer la longueur du nom de la variable.
	var_name_len = 2;

	// Extraire la partie de la chaîne avant le nom de la variable.
	tmp = ft_substr(input_str, 0, start);

	// Concaténer la partie précédente de la chaîne avec la valeur de la variable.
	tmp2 = ft_strjoin(tmp, var_value);
	free(tmp);

	// Concaténer le résultat précédent avec la partie de la chaîne après le nom de la variable.
	result = ft_strjoin(tmp2, &input_str[start + var_name_len]);
	free(tmp2);


	return (result);
}

int	replace_with_values(char **input, char ***var_values_tab)
{
	int		i;
	char	*input_str;
	char	*new_input;
	char	*status;
	int		is_var;

	input_str = *input;
	status = NULL;
	i = 0;
	is_var = 0;
	
	while (input_str[i])
	{
		if (input_str[i] == '$' && check_inside_simple_quote(input_str, i) != SUCCESS)
		{
			
			if (ft_strncmp(&input_str[i], "$?", 2) == 0)
			{
			// printf("print status ");
			// printf("%s\n", &input_str[i + 1]);
				status = ft_itoa(global_env->status);
				new_input = replace_var_status_in_string(input_str, &i, status);
				i = i + 1;
				free(status);
			// new_input = ft_itoa(global_env->status);
			}
			else if (input_str[i + 1] == ' ' || input_str[i + 1] == '\0' || !ft_isalnum(input_str[i + 1]))
			{
				i++;
				continue;
			}
			// if (ft_strncmp(&input_str[i], "$?", 2) == 0)
			// {
			// 	// printf("print status ");
			// 	// printf("%s\n", &input_str[i + 1]);
			// 	replace_var_in_string(input_str, &i, global_env->status)
			// 	// new_input = ft_itoa(global_env->status);
			// }
			else
			{
				new_input = replace_var_in_string(input_str, &i, *var_values_tab);
				i--;
				// printf("var_value found: %s\n", new_input);
			}
			if (input_str != new_input)
			{
				free(input_str);
				input_str = new_input;
				is_var = 1;
			}
		}
		else
		{
			i++;
		}
	}
	
	*input = input_str;  // Pas besoin de vérifier si new_input est non NULL car input_str pointera toujours vers la dernière version de la chaîne
	
	return (is_var);
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
		var_value = ft_strdup("");
	free(var_name);
	return (var_value);
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
