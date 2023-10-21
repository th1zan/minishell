/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:07:23 by thibault          #+#    #+#             */
/*   Updated: 2023/10/17 22:42:00 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	malloc_strtab(char ***strtab, int nbstr)
{
	*strtab = (char **)ft_calloc((nbstr + 1), sizeof(char *));
	if (!(*strtab))
		return (1);
	// printf("malloc_strtab: calloc strtab %p\n", strtab);
	(*strtab)[nbstr] = NULL;
	return (0);
}

int	free_strtab(char **strtab)
{
	int	i;

	i = 0;
	while (strtab[i] != NULL)
	{
		// printf("free strtab[%d] %s, %p\n", i, strtab[i], strtab[i]);
		free(strtab[i]);
		strtab[i] = NULL;
		i++;
	}
	// free(strtab);
	return (0);
}

int	free_strtab_env(char **strtab)
{
	int	i;

	i = 0;
	while (strtab[i] != NULL)
	{
		// printf("free strtab[%d] %s, %p\n", i, strtab[i], strtab[i]);
		free(strtab[i]);
		strtab[i] = NULL;
		i++;
	}
	// free(strtab);
	return (0);
}

int	print_strtab(char **strtab, int fd_out)
{
	int	i;

	// printf("tab: %p\n", strtab);
	i = 0;
	while (strtab[i] != NULL)
	{
		
		ft_putstr_fd(strtab[i], fd_out);
		ft_putstr_fd("\n", fd_out);
		// printf("%s, %p\n", strtab[i], strtab[i]);
		i++;
	}
	return (0);
}
