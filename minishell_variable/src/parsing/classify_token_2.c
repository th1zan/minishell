/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:04:53 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 22:05:43 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_arg_tk(t_tk *tk)
{
	t_tk	*tmp;

	tmp = tk;
	while (tmp)
	{
		if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
		{
			tmp = tmp->next;
			while (tmp && (tmp->type != TK_PIPE))
			{
				if (tmp->type == TK_CMD || tmp->type == TK_CMD_BUILT_IN)
					tmp->type = TK_ARG;
				tmp = tmp->next;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	move_args_to_sublist(tk);
	return (0);
}

int	open_temp_file(t_tk *tk, char **temp_file_path)
{
	*temp_file_path = ft_strjoin(tk->env_struct->minishell_directory,
			"/hd_arg.txt");
	unlink(*temp_file_path);
	tk->fd_in = open(*temp_file_path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	return (tk->fd_in);
}

int	write_to_temp_file(int fd, char *input)
{
	if (write(fd, input, ft_strlen(input)) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (0);
}

void	free_memory_and_close_fd(int *fd, char **file_path)
{
	if (*fd >= 0)
		close(*fd);
	if (*file_path)
	{
		unlink(*file_path);
		free(*file_path);
	}
}

int	process_hd_arg(t_tk *tk, char **temp_file_path)
{
	char	*input;

	if (!tk || tk->type != TK_HD_ARG || !tk->prev)
		return (0);
	if (open_temp_file(tk, temp_file_path) == -1)
		return (-1);
	free(tk->prev->tk_str);
	tk->prev->tk_str = *temp_file_path;
	while (1)
	{
		input = get_line("heredoc> ");
		if (!ft_strncmp(input, tk->tk_str, ft_strlen(tk->tk_str)))
		{
			free(input);
			break ;
		}
		if (write_to_temp_file(tk->fd_in, input) == -1)
		{
			free(input);
			return (-1);
		}
		free(input);
	}
	return (0);
}
