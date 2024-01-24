/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_operator_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:54:48 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 14:08:17 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_dup2_input_error(int fd_in)
{
	perror("dup2 input error");
	close(fd_in);
	return (-1);
}

int	handle_dup2_output_error(int fd_out)
{
	perror("dup2 output error");
	close(fd_out);
	return (-1);
}

int	redirect_input(t_tk *token)
{
	if (dup2(token->fd_in, STDIN_FILENO) == -1)
		return (handle_dup2_input_error(token->fd_in));
	return (0);
}

int	redirect_output(t_tk *token)
{
	if (dup2(token->fd_out, STDOUT_FILENO) == -1)
		return (handle_dup2_output_error(token->fd_out));
	return (0);
}

int	process_redirection(t_tk *token)
{
	if (token->type == TK_IN_CHEVRON || token->type == TK_HERE_DOC)
		return (redirect_input(token));
	else if (token->type == TK_OUT_CHEVRON || token->type == TK_APP_CHEVRON)
		return (redirect_output(token));
	return (0);
}
