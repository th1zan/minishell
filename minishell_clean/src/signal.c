/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:54:14 by thibault          #+#    #+#             */
/*   Updated: 2023/11/07 22:18:15 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std(int *original_std)
{
	original_std[0] = dup(STDIN_FILENO);
	original_std[1] = dup(STDOUT_FILENO);
	original_std[2] = dup(STDERR_FILENO);
	if (original_std[0] == -1 || original_std[1] == -1 || original_std[2] == -1)
	{
		perror("dup error: original_std[0] in save_std");
		return (-1);
	}
	return (0);
}

int	restore_std(int *original_std)
{
	if (dup2(original_std[0], STDIN_FILENO) == -1)
	{
		perror("dup2 error: original_std[0] in restore_std");
		return (-1);
	}
	if (dup2(original_std[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 error: original_std[1] in restore_std");
		return (-1);
	}
	if (dup2(original_std[2], STDERR_FILENO) == -1)
	{
		perror("dup2 error: original_std[2] in restore_std");
		return (-1);
	}
	close(original_std[0]);
	close(original_std[1]);
	close(original_std[2]);
	return (0);
}

void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN); // Ctrl + backslash
	signal(SIGINT, handle_sigint); //Ctrl + C
}

void	handle_sigint(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	g_env->status = 1;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	create_history(char *input)
{
	int	fd;

	add_history(input);
	fd = open("history.log", O_CREAT | O_WRONLY | O_APPEND, 0777);
	ft_putstr_fd(input, fd);
	ft_putstr_fd("\n", fd);
}
