/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:57:52 by thibault          #+#    #+#             */
/*   Updated: 2023/08/10 09:35:52 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_tk	*ft_lstlast(t_tk *tk)
{
	if (!tk)
		return (0);
	while (tk->next != 0)
		tk = tk->next;
	return (tk);
}

int	ft_lstsize(t_tk *tk)
{
	int	n;

	n = 0;
	while (tk != 0)
	{
		tk = tk->next;
		n++;
	}
	return (n);
}

int	print_lst(t_tk *tk)
{
	
	if (!tk)
	{
		ft_putstr_fd("tk vide\n", 1);
		return (0);
	}
	if (tk->prev == NULL)
	{
		printf("\n-----PRINT LST--------\n");
	}
	// Print list
	while (tk != NULL)
	{
		
		fprintf(stderr,"%-15s ||", tk->tk_str);
		fprintf(stderr," tk_addr: %-15p", tk);
		fprintf(stderr," tk_type: %-5d", tk->type);
		fprintf(stderr," fd_in: %-5d", tk->fd_in);
		fprintf(stderr," fd_out: %-5d", tk->fd_out);
		// fprintf(stderr," prev_tk: %-15p", tk->prev);
		fprintf(stderr," next_tk: %-15p\n", tk->next);
		// Print sublist
		if (tk->tk_arg)
		{
			fprintf(stderr,"\n%-5s ----->PRINT ARG--------\n", "");
			print_lst(tk->tk_arg);
		}
		if (tk->next == NULL)
		{
			if (tk->type == TK_FILE || tk->type == TK_ARG)
			{
				fprintf(stderr,"\n%-5s ----->END PRINT ARG------\n\n", "");
			}
			else
			{
				fprintf(stderr,"\n-----END PRINT LST--------\n\n");
			}
		}
		tk = tk->next;
	}
	return (1);
}

int	free_env(t_env *env)
{	
	if (env)
	{	
		printf("free env_main: %p\n", env->env_main);
		if(env->env_main)
		{	
			// print_strtab(env->env_main);
			free_strtab_env(env->env_main);
			free(env->env_main);
		}
		
		free(env);
	}
	printf("free env: %p\n", env);
	
	return (0);
}

int	free_lst(t_tk *head_list)
{
	t_tk	*tmp;

	
	while (head_list != NULL)
	{
		tmp = head_list->next;
		// printf("befor condition: head_list path_tab: %p\n", head_list->path_tab);
		// if (head_list->path_tab)
		// {	
		// 	printf("free head_list path_tab: %p\n", head_list->path_tab);
		// 	free_strtab(head_list->path_tab);
		// 	head_list->path_tab = NULL;
		// }
		free_elem(head_list);
		head_list = tmp;
	}

	
	return (0);
}

int	free_elem(t_tk *token)
{
	t_tk	*tmp;
	t_tk 	*tmp_arg;
	
	// printf("Trying to free token : %p\n",token);

	if(token->tk_str)
	{
		// printf("free token_str: %s, %p\n",token->tk_str, token->tk_str);
		free(token->tk_str);
		token->tk_str = NULL;
	}	
		
	// if(token->path)
	// {
	// 	printf("free token_path: %s, %p\n",token->path, token->path);
	// 	free(token->path);
	// 	token->path = NULL;
	// }
	// if(token->path_tab)
	// {
	// 	printf("free path_tab: %p\n",token->path_tab);
	// 	free_strtab(token->path_tab);
	// 	token->path_tab = NULL;
	// }	
	if(token->tk_arg)
	{
		tmp = token->tk_arg;
		while (tmp != NULL)
		{
			tmp_arg = tmp->next; // save next tk
			free_elem(tmp); // free current
			tmp = tmp_arg; // current = next tk
		}
	}
	free(token);
	return (0);
}


// typedef struct s_tk
// {
// 	char		*tk;
// 	char		*type;
// 	char		*tk_arg_str;
// 	struct s_tk	*tk_arg;
// 	struct s_tk	*prev;
// 	struct s_tk	*next;
// }	t_tk;

// TEST Minishell
// < "file entree.txt" wc -l ||         ls  -l << 'output de sortie'