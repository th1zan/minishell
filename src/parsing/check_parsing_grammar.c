/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_grammar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:42:49 by thibault          #+#    #+#             */
/*   Updated: 2023/08/29 16:25:42 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Vérifie le premier et le dernier token de la liste principale
int	check_first_last_token(t_tk *first, t_tk *last)
{
	if (!(is_tk_redir(first->type) || first->type == TK_CMD)) {
		printf("error: first TK is not redir_operator or CMD");
		return (1);
	}
	if (!(is_tk_redir(last->type) || last->type == TK_CMD || last->type == TK_PIPE)) {
		printf("error: last TK is not redir_operator or CMD or PIPE");
		return (1);
	}
	return (0);
}

// Vérifie les tokens dans la liste principale
int	check_main_list_tokens(t_tk *tk)
{
	t_tk *tmp = tk->next;
	t_tk *prev = tk;
	while (tmp != NULL) {
		if (prev->type == TK_CMD && !(is_tk_redir(tmp->type) || tmp->type == TK_PIPE)) {
			printf("error: prev TK is CMD and current TK is not a redir_operator OR a pipe\n");
			return (1);
		}
		if ((is_tk_redir(prev->type) || prev->type == TK_PIPE) && tmp->type != TK_CMD) {
			printf("error: prev TK is a redir_operator OR a pipe and current TK is not CMD\n");
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

// Vérifie les sous-listes pour les tokens de type redirection
int	check_redir_sublist(t_tk *tk)
{
	if (tk->tk_arg == NULL || tk->tk_arg->next != NULL) {
		printf("error: redirection operator without file\n");
		return (1);
	}
	if (tk->tk_arg->type != TK_FILE) {
		printf("error: redirection operator has a wrong type arg\n");
		return (1);
	}
	return (0);
}

// Vérifie les sous-listes pour les tokens de type HERE_DOC
int	check_here_doc_sublist(t_tk *tk)
{
	t_tk *arg = tk->tk_arg;
	while (arg) {
		if (arg->type != TK_HD_ARG) {
			printf("error: here-doc operator has a wrong type arg\n");
			return (1);
		}
		arg = arg->next;
	}
	return (0);
}

// Vérifie les sous-listes pour les tokens de type CMD
int	check_cmd_sublist(t_tk *tk)
{
	t_tk *arg = tk->tk_arg;
	while (arg) {
		if (arg->type != TK_ARG) {
			printf("error: TK_CMD has a wrong type arg\n");
			return (1);
		}
		arg = arg->next;
	}
	return (0);
}

// Fonction principale
int	check_grammar(t_tk *tk)
{
	if (!tk) {
		printf("error - no argument\n");
		return (0);
	}

	if (check_first_last_token(tk, tk) != 0) return (1);
	if (check_main_list_tokens(tk) != 0) return (1);

	t_tk *tmp = tk;
	while (tmp != NULL) {
		if (is_tk_in_out_app(tmp->type)) {
			if (check_redir_sublist(tmp) != 0) return (1);
		} else if (tmp->type == TK_PIPE) {
			if (tmp->tk_arg != NULL) {
				printf("error: pipe operator has an argument, it should not\n");
				return (1);
			}
		} else if (tmp->type == TK_HERE_DOC) {
			if (check_here_doc_sublist(tmp) != 0) return (1);
		} else if (tmp->type == TK_CMD) {
			if (check_cmd_sublist(tmp) != 0) return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
