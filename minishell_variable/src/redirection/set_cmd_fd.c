/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:40:14 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 14:30:01 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_cmd_std_fd(t_tk **tk)
{
	t_tk		*tmp;

	tmp = *tk;
	while (tmp != NULL)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			if (tmp->prev == 0)
				tmp->fd_in = STDIN_FILENO;
			if (tmp->next == 0)
				tmp->fd_out = STDOUT_FILENO;
		}
		tmp = tmp->next;
	}
	return (0);
}


// Vérifie la présence de chevrons entre les tokens
int	chevron_out_between_pipe_and_cmd(t_tk *start, t_tk *end)
{
	t_tk *tmp;

	tmp = start->next;
	while (tmp && tmp->type != TK_PIPE)
	{
		if (tmp->type == TK_APP_CHEVRON || tmp->type == TK_OUT_CHEVRON)
			return (1);
		if (tmp == end)
			break;
		tmp = tmp->next;
	}
	return (0);
}

int	chevron_in_between_pipe_and_cmd(t_tk *start, t_tk *end)
{
	t_tk *tmp;

	// printf("start : %s\n", start->tk_str);
	// printf("end : %s\n", end->tk_str);
	tmp = start->next;
	// printf("tmp : %s\n", tmp->tk_str);
	while (tmp && tmp->type != TK_PIPE)
	{
		// printf("tmp %s type: %d\n", tmp->tk_str,tmp->type);
		if (tmp->type == TK_IN_CHEVRON)
			return (1);
		if (tmp == end)
			break;
		tmp = tmp->next;
	}
	return (0);
}

int	set_cmd_pipe_fd(t_tk **tk)
{
	t_tk *tmp;
	t_tk *prev_pipe;
	t_tk *next_pipe;

	// print_lst(*tk);
	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			prev_pipe = get_prev_pipe_tk(tmp);
			next_pipe = get_next_pipe_tk(tmp);
			if (prev_pipe)
			{
				if (!chevron_in_between_pipe_and_cmd(prev_pipe, tmp) && 
					!(next_pipe && chevron_in_between_pipe_and_cmd(tmp, next_pipe)) &&
					!(next_pipe == NULL && chevron_in_between_pipe_and_cmd(tmp, ft_lstlast(tmp))))
				{
					tmp->fd_in = prev_pipe->fd_out;
				}
			}
			if (next_pipe)
			{
				// if (!chevron_out_between_pipe_and_cmd(tmp, next_pipe))
				// 	printf("C1\n");
				// if	(!(prev_pipe && chevron_out_between_pipe_and_cmd(prev_pipe, tmp)))
				// 	printf("C2\n");
				// if	(!(prev_pipe == NULL && chevron_out_between_pipe_and_cmd(ft_lstfirst(tmp), tmp)))
				// 	printf("C3\n");
					
				if (!chevron_out_between_pipe_and_cmd(tmp, next_pipe) &&
					!(prev_pipe && chevron_out_between_pipe_and_cmd(prev_pipe, tmp)) &&
					!(prev_pipe == NULL && chevron_out_between_pipe_and_cmd(ft_lstfirst(tmp), tmp)))
				{
					tmp->fd_out = next_pipe->fd_in;
				}
			}
		}
		tmp = tmp->next;
	}
	
	return (0);
}


// Configure les descripteurs de fichier pour les commandes dans le pipeline

// int	set_cmd_pipe_fd(t_tk **tk)
// {
// 	t_tk *tmp;
// 	t_tk *prev_pipe;
// 	t_tk *next_pipe;

// 	tmp = *tk;
// 	while (tmp)
// 	{
// 		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
// 		{
// 			prev_pipe = get_prev_pipe_tk(tmp);
// 			next_pipe = get_next_pipe_tk(tmp);
// 			if (prev_pipe && !chevron_in_between(prev_pipe, tmp))
// 				tmp->fd_in = prev_pipe->fd_out;
// 			if (next_pipe && !chevron_in_between(tmp, next_pipe))
// 				tmp->fd_in = prev_pipe->fd_out;
// 			if (prev_pipe && !chevron_out_between(prev_pipe, tmp))
// 				tmp->fd_in = prev_pipe->fd_out;
// 			if (next_pipe && !chevron_out_between(tmp, next_pipe))
// 				tmp->fd_out = next_pipe->fd_in;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

void	set_fd_in(t_tk *tmp)
{
	t_tk	*input_operator;

	input_operator = get_prev_input_operator_tk(tmp);
	if (input_operator == NULL)
		input_operator = get_next_input_operator_tk(tmp);
	if (input_operator != NULL)
		tmp->fd_in = input_operator->fd_in;
	else
		tmp->fd_in = 0;
}

void	set_fd_out(t_tk *tmp)
{
	t_tk	*output_operator;

	output_operator = get_prev_output_operator_tk(tmp);
	if (output_operator == NULL)
		output_operator = get_next_output_operator_tk(tmp);
	if (output_operator != NULL)
		tmp->fd_out = output_operator->fd_out;
	else
		tmp->fd_out = 1;
}

int	set_cmd_operator_fd(t_tk **tk)
{
	t_tk	*tmp;

	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			set_fd_in(tmp);
			set_fd_out(tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
