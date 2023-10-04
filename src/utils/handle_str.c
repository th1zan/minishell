/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:31:29 by thibault          #+#    #+#             */
/*   Updated: 2023/10/04 14:53:26 by tsanglar         ###   ########.fr       */
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


// int	count_variables(char *input)
// {
// 	int count = 0;
// 	int i = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == '$' && check_inside_simple_quote(input, i) != SUCCESS)
// 		{
// 			count++;
// 			i++;
// 			while (is_portable_filename_char(input[i]) && input[i] != 0)
// 				i++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (count);
// }

// char	**get_variables_values(char *input)
// {
// 	int n_variables;
// 	char **var_values_tab;;
// 	int i;
// 	int j;
// 	int start;

// 	n_variables = count_variables(input);
// 	var_values_tab = (char **)malloc((n_variables + 1) * sizeof(char *));
// 	if (!var_values_tab)
// 		return(NULL);
// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	while (input[i] && j < n_variables)
// 	{
// 		if (input[i] == '$' && check_inside_simple_quote(input, i) != SUCCESS)
// 		{
// 			start = i;
// 			i++;
// 			while (is_portable_filename_char(input[i]) && input[i] != 0)
// 				i++;
// 			char *variable_name = ft_substr(input, start + 1, i - start - 1);
// 			// var_values_tab[j] = get_env_variable(variable_name);
// 			var_values_tab[j] = ft_strdup("VALEUR_VARIABLE"); 
// 			free(variable_name);
// 			j++;
// 		}
// 		else
// 			i++;
// 	}
// 	var_values_tab[j] = NULL;
// 	return (var_values_tab);
// }

// char *get_var_value(char *input, int i, char **var_values_tab)
// {
// 	int		end;
// 	char	*var_name;
// 	char	*var_value;

// 	end = 0;
// 	var_name = NULL;
// 	var_value = NULL;
// 	i++;
// 	while (is_portable_filename_char(input[i + end]) == 1)
// 	{	
// 		end++;
// 	}
// 	printf("end: %d\n", end);
	
// 	var_name = ft_substr(input, i, end);
	

// 	i = 0;
// 	while(var_values_tab[i])
// 	{
// 		printf("var_name: %s\n", var_name);
// 		printf("var_value_tab: %s\n", var_values_tab[i]);
// 		if (ft_strncmp(var_name, var_values_tab[i], ft_strlen(var_name)) == 0)
// 			break;
// 		i++;
// 	}
// 	var_value = var_values_tab[i];
	
// 	printf("var_value: %s/n", var_value);
// 	i = 0;
// 	if (var_value != NULL)
// 	{
// 		while (var_value[i] != '=')
// 			i++;
// 		i++;
// 		var_value = ft_substr(var_value, i, ft_strlen(var_value) - i);
// 		printf("var_value substr: %s/n", var_value);

// 	}
// 	else
// 		var_value = ft_strdup(" ");
	
// 	free(var_name);
// 	return (var_value);
// }

// int	replace_with_values(char **input, char **var_values_tab)
// {
// 	char	*new_input;
// 	char	*tmp;
// 	char	*tmp2; 
// 	int		i;
// 	int		j;
// 	int		start;
// 	char	*input_str;
// 	char	*var_value;
// 	(void)var_values_tab;
	

// 	input_str = *input;
// 	new_input = ft_strdup("");
// 	// var_value = NULL;
// 	var_value = "TEST";
// 	i = 0;
// 	j = 0;
// 	start = 0;

// 	while (input_str[i])
// 	{
		

// 		if (input_str[i] == '$' && check_inside_simple_quote(input_str, i) != SUCCESS)
// 		{
// 			tmp = ft_substr(input_str, start, i - start);
// 			tmp2 = ft_strjoin(tmp, new_input);

// 			free(new_input);
// 			var_value = get_var_value(input_str, i, var_values_tab);
// 			new_input = ft_strjoin(tmp2, var_value);
// 			free(tmp2);
// 			free(tmp);
// 			i++;
// 			while (is_portable_filename_char(input_str[i]))
// 			{	
				
// 				i++;
// 			}
// 			start = i;
// 			j++;
// 		}
// 		else
// 			i++;
// 	}


// 	if(new_input != NULL)
// 	{
// 		tmp = ft_strjoin(new_input, &input_str[start]);
// 		free(new_input);
// 		free(input_str);
// 		// free(var_value);
// 		*input = tmp;
// 	}
	

// 	return (0);

// }

char *get_var_name_from_input(char *input, int *i)
{
	int		end = 0;
	(*i)++;
	while (is_portable_filename_char(input[*i + end]) == 1) { end++; }
	return ft_substr(input, *i, end);
}

char *find_value_in_tab(char *var_name, char **var_values_tab)
{
	int i = 0;
	while(var_values_tab[i])
	{
		if (ft_strncmp(var_name, var_values_tab[i], ft_strlen(var_name)) == 0)
			return var_values_tab[i];
		i++;
	}
	return NULL;
}

char *get_value_after_equal(char *var_value)
{
	int i = 0;
	while (var_value && var_value[i] != '=') { i++; }
	i++;
	return ft_substr(var_value, i, ft_strlen(var_value) - i);
}

char *replace_var_in_string(char *input_str, char *new_input, int *i, char **var_values_tab)
{
	char	*tmp;
	char	*tmp2; 
	char	*var_value;

	tmp = ft_substr(input_str, 0, *i);
	tmp2 = ft_strjoin(tmp, new_input);
	free(new_input);
	var_value = get_var_value(input_str, i, var_values_tab);
	new_input = ft_strjoin(tmp2, var_value);
	free(tmp2);
	free(tmp);
	return new_input;
}

int	replace_with_values(char **input, char ***var_values_tab)
{
	char	*new_input;
	int		i;
	int		start;
	char	*input_str;
	char	*tmp;
	
	input_str = *input;
	new_input = ft_strdup("");
	i = 0;
	start = 0;

	while (input_str[i])
	{
		if (input_str[i] == '$' && check_inside_simple_quote(input_str, i) != SUCCESS)
		{
			new_input = replace_var_in_string(input_str, new_input, &i, *var_values_tab);
			while (is_portable_filename_char(input_str[i])) { i++; }
			start = i;
		}
		else
			i++;
	}
	
		if(new_input != NULL)
	{
		tmp = ft_strjoin(new_input, &input_str[start]);
		free(new_input);
		free(input_str);
		// free(var_value);
		*input = tmp;
	}
	

	return (0);
}

char *get_var_value(char *input, int *i, char **var_values_tab)
{
	char	*var_name;
	char	*var_value_tab;
	char	*var_value;

	var_name = get_var_name_from_input(input, i);
	var_value_tab = find_value_in_tab(var_name, var_values_tab);
	var_value = get_value_after_equal(var_value_tab);
	if (!var_value)
		var_value = ft_strdup(" ");
	free(var_name);
	return var_value;
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
