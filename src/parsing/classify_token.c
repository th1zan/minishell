/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:26:16 by thibault          #+#    #+#             */
/*   Updated: 2023/10/30 15:27:22 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_arg_to_sublist(t_tk **tmp, t_tk **sublst_last, t_tk *cmd, t_tk **last_non_arg)
{
	t_tk	*next = (*tmp)->next; // Sauvegarder le token suivant

	// Détacher le token actuel de la liste principale
	if ((*tmp)->prev)
		(*tmp)->prev->next = (*tmp)->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = (*tmp)->prev;

	if (*sublst_last) // S'il y a déjà des arguments dans la sous-liste
	{
		// Ajouter le token actuel à la fin de la sous-liste
		(*tmp)->prev = *sublst_last;
		(*sublst_last)->next = *tmp;
	}
	else // Si c'est le premier argument de la sous-liste
	{
		cmd->tk_arg = *tmp; // Mettre à jour la tête de la sous-liste
		(*tmp)->prev = NULL; // Il est maintenant en tête de la sous-liste
	}
	(*tmp)->next = NULL; // Il est maintenant à la fin de la sous-liste

	*sublst_last = *tmp; // Mettre à jour le dernier argument de la sous-liste

	// Si last_non_arg n'est pas un argument, son 'next' doit pointer vers le prochain non-arg ou null
	if (*last_non_arg && (*last_non_arg)->type != TK_ARG)
		(*last_non_arg)->next = next;

	*tmp = next; // Passer au token suivant dans la liste principale
}

t_tk	*move_args_to_sublist(t_tk *tk)
{
	t_tk	*tmp = tk;
	t_tk	*cmd = NULL;
	t_tk	*last_non_arg = NULL; // Dernier token qui n'est pas de type TK_ARG
	t_tk	*sublst_last = NULL; // Dernier argument dans la sous-liste

	while (tmp)
	{
		if (tmp->type == TK_CMD)
		{
			cmd = tmp;
			last_non_arg = tmp; // Le dernier non-arg est la commande pour le moment
			sublst_last = NULL; // Réinitialiser pour la nouvelle commande
			tmp = tmp->next; // Avancer au token suivant après avoir trouvé une commande

			while (tmp && tmp->type != TK_PIPE) // Boucle jusqu'au prochain pipe
			{
				if (tmp->type == TK_ARG) // Si c'est un argument, déplacez-le sous la commande
				{

					move_arg_to_sublist(&tmp, &sublst_last, cmd, &last_non_arg);
					handle_quotes(tmp);
				}
				else
				{
					last_non_arg = tmp; // Si ce n'est pas un argument, c'est le dernier non-arg
					tmp = tmp->next; // Passer au token suivant dans la liste principale
				}
			}
		}
		else
		{
			tmp = tmp->next; // Si ce n'est pas une commande, passer simplement au token suivant
		}

		// Si nous atteignons un pipe, nous devons arrêter de regrouper les arguments sous la commande actuelle
		if (tmp && tmp->type == TK_PIPE)
			tmp = tmp->next; // Passer au token suivant après le pipe
	}

	return tk; // Retourner la tête modifiée de la liste principale
}


int	ft_handle_arg_tk(t_tk *tk)
{
	t_tk	*tmp;
	
	//classify token as COMMAND or ARGUMENT
	// tmp = get_next_type_tk(tk, TK_CMD);
	// if (tk->type != TK_CMD)
	// 	tmp = get_next_type_tk(tmp, TK_CMD);	
	// while (tmp)
	// {
	// 	printf("tk: %s, %d\n", tmp->tk_str, tmp->type);
	// 	tmp->type = TK_ARG;
	// 	delete_quotes(&(tmp->tk_str));
	// 	if (tmp->next && tmp->next->type == TK_PIPE)
	// 		tmp = get_next_type_tk(tmp, TK_CMD);
	// 	tmp = get_next_type_tk(tmp, TK_CMD);
		
	// }
	
	tmp = tk;
	while (tmp)
	{
		if (tmp->type == TK_CMD)
		{
			
			tmp = tmp->next;
			while (tmp && (tmp->type != TK_PIPE))
			// while (tmp && is_tk_redir(tmp->type))
			{
				// printf("AVANT tmp: %s, type: %d %p\n", tmp->tk_str, tmp->type, tmp->next);
				if (tmp->type == TK_CMD)
					tmp->type = TK_ARG;
				// printf("APRES tmp: %s, type: %d %p\n", tmp->tk_str, tmp->type, tmp->next);
				tmp = tmp->next;
			}
		}
		// printf("1 tmp: %s\n", tmp->tk_str);
		if (tmp)
			tmp = tmp->next;
			
	}
	// printf("3 tmp: %s\n", tmp->tk_str);
	
	move_args_to_sublist(tk);


	// tmp = tk;
	// while (tmp)
	// {
	// 	tk_cmd = get_next_type_tk(tmp, TK_CMD);
	// 	tk_cmd->tk_arg = get_next_type_tk(tk_cmd, TK_ARG);
	// 	//changer les liaisons 
	// 	tk_arg_first = tk_cmd->tk_arg;
	// 	tmp = get_next_type_tk(tk_cmd, TK_ARG);
		


	// 	tmp = get_next_type_tk(tk_cmd, TK_CMD);
	// }
	return (0);
}



int	ft_handle_hd_arg_tk(t_tk *tk)
{
	char	*input;
	char	*tmp_hd_arg_file;
	int		fd_tmp;
	ssize_t	bytes_written;
	int		hd_arg_exist;

	tmp_hd_arg_file = ft_strjoin(global_env->minishell_directory, "/hd_arg.txt");
	// printf("%s\n", tmp_hd_arg_file);
	// Supprimer le fichier
	unlink(tmp_hd_arg_file);
	fd_tmp = open(tmp_hd_arg_file, O_CREAT | O_APPEND | O_WRONLY, 0777);
	hd_arg_exist = 0;
	if (fd_tmp == -1)
	{
		perror("minishell: Error opening here-doc tmp file");
		// printf("FREE 1\n");
		// printf("FREE 1: tk->prev->tk_str: %s %p\n", tk->prev->tk_str, tk->prev->tk_str);
		free(tmp_hd_arg_file);
		return (1);
	}

	if (!tk)
	{
		close(fd_tmp);
		// printf("FREE 2\n");
		// printf("FREE 2: tk->prev->tk_str: %s %p\n", tk->prev->tk_str, tk->prev->tk_str);
		free(tmp_hd_arg_file);
		return (1);
	}

	while (tk)
	{	
		if (tk->type == TK_HD_ARG)
		{	
			if(tk->prev->tk_str)
			{	
				// printf("FREE 3\n");
				// printf("FREE 3: tk->prev->tk_str: %s %p\n", tk->prev->tk_str, tk->prev->tk_str);
				free(tk->prev->tk_str);
				tk->prev->tk_str = NULL;
			}
			while(1)
			{
				input = get_line("heredoc> ");
				if (!input)
				{
					printf("minishell: error: here-doc get_line returned NULL\n");
					continue;
				}
				replace_with_values(&input, &global_env->env_main);
				if (!ft_strncmp(input, tk->tk_str, ft_strlen(tk->tk_str)))
					break;
				bytes_written = write(fd_tmp, input, ft_strlen(input));
				write(fd_tmp, "\n", 1);
				if (bytes_written == -1)
				{
					perror("Error writing to file");
				}
				free(input);
				tk->prev->tk_str = tmp_hd_arg_file;
				hd_arg_exist = 1;
			}
		}
		tk = tk->next;
	}			
	close(fd_tmp);
	// printf("FREE 4\n");
	// printf("FREE 4: tmp_hd_arg_file: %s %p\n", tmp_hd_arg_file, tmp_hd_arg_file);
	if (!hd_arg_exist)
		free(tmp_hd_arg_file);
	return (0);
}


/*After the operator < > >> , there is a file. The file is an "argument" (sublist) of the operator*/
int	ft_handle_file_tk(t_tk *tk)
{

	t_tk *tk_file;
	
	if (!(tk))
		return (1);
	while (tk)
	{
		
		if (is_tk_in_out_app(tk->type) && tk->next)
		{
			tk_file = tk->next;
			tk_file->type = TK_FILE;
			tk->next = tk_file->next;
			tk->tk_arg = tk_file;
			if (tk_file->next)
			{
				tk_file->next->prev = tk;
			}
			tk_file->next = NULL;
			
		}
		tk = tk->next;
			
	}
		// printf("OUT-> str:%s type: %d \n", tk->tk_str, tk->type);
		return (0);

	// TODO: Gérer les erreur : 
	// - operateur de redirecton non suivi par un nom de fichier: syntax error: unexpected end of file
	// - opérateur suivi par plus de 1 nom de fichier 
	// - nom de fichier invalide
	
}


int	ft_handle_built_in(t_tk *tk)
{

	t_tk *tmp;
	
	if (!(tk))
		return (1);
	tmp = tk;
	while (tmp)
	{
		
		if (tmp->type == TK_CMD)
		{
			if(is_builtin_cmd_tk(tmp) == 1)
			{
				tmp->type = TK_CMD_BUILT_IN;
				// printf("%d : TK %s is a BUILT IN\n", is_builtin_cmd_tk(tmp), tmp->tk_str);
			}
		}
		tmp = tmp->next;
	}
		// printf("OUT-> str:%s type: %d \n", tk->tk_str, tk->type);
		return (0);

	
}