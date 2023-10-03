/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:23:51 by tsanglar          #+#    #+#             */
/*   Updated: 2023/10/03 13:57:32 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	create_envir(t_env **env_head, char **env)
// {
// 	int	len;
// 	int	i:

// 	len = 0;
// 	while(env[len])
// 		len++;

	


// 	return(0);
// }


	// ft_lstadd_back_env(env_head, ft_lstnew_env(env[i]));

	// ft_lst_modif_tk_str_env(*env_head, del_whitespace);


// void	ft_lstadd_back_env(t_env **env_head, t_env *new_env)
// {
// 	t_env	*tk_end;

// 	tk_end = ft_lstlast(*env_head);
// 	if (tk_end == 0)
// 		*head_tk_tk = new_tk;
// 	else
// 	tk_end->next = new_tk;
// 	new_tk->prev = tk_end;
// }

// t_env	*ft_lstlast_env(t_env *tk)
// {
// 	if (!tk)
// 		return (0);
// 	while (tk->next != 0)
// 		tk = tk->next;
// 	return (tk);
// }

// t_env	*ft_lstnew_env(char *env_str)
// {
// 	t_env	*new_tk;

// 	new_tk = (t_tk *)calloc(1, sizeof(t_tk));
// 	if (!new_tk)
// 		return (NULL);

// 	new_tk->var_name = env_str;
// 	return (new_tk);
// }

// void	ft_lst_modif_tk_str_env(t_env *tk, int (*f)(char **str))
// {
// 	if (!(tk) || !(f))
// 		return ;
// 	while (tk)
// 	{
// 		(f)(&tk->tk_str);
// 		tk = tk->next;
// 	}
// }

// void	get_env_tab_var_values(t_env *tk, int (*f)(char **str))
// {
// 	if (!(tk) || !(f))
// 		return ;
// 	while (tk)
// 	{
// 		tk->var_values = (f)(&tk->tk_str);
// 		tk = tk->next;
// 	}
// }

// int	del_var_values(char **str)
// {
// 	int		begin;
// 	int		end;
// 	int		len;
// 	char	*temp;

// 	//for (int i = 0; str[i]; i++) {
// 	//	printf("str[%d] : %s\n", i, str[i]);
// 	//}

// 	if (!*str || **str == '\0')
// 		return (0);
// 	begin = 0;
// 	while(str[begin])
// 	{
// 		if (!str[begin])
// 			break;
// 		return(0);
// 	}
// 	begin = 0;
// 	while ((*str)[begin] != '=')
// 		begin++;
// 	end = ft_strlen(*str) -1;
// 	len = end - begin + 1;
// 	temp = *str;
// 	*str = ft_substr(temp, begin, len);
// 	free(temp);
// 	return (0);
// }

// char	**get_var_values(char *env)
// {
// 	char	**var_values;
// 	int		i;

// 	path = NULL;
// 	i = 0;
	
// 	while (env[i] != 0)
// 	{
// 		if (ft_strnstr(env[i], "=", 1) != 0)
// 			break;
// 		i++;
// 	}
// 	path = ft_split(env[i], ':');
// 	// printf("IN SPLIT: path adress:%p\n", path);
// 	return (path);
// }