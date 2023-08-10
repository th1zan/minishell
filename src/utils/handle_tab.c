/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:07:23 by thibault          #+#    #+#             */
/*   Updated: 2023/08/09 22:50:35 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	malloc_strtab(char ***strtab, int nbstr)
{
	*strtab = (char **)malloc(sizeof(char *) * (nbstr + 1));
	if (!(*strtab))
		return (1);
	(*strtab)[nbstr] = NULL;
	return (0);
}

int	free_strtab(char **strtab)
{
	int	i;

	i = 0;
	while (strtab[i] != NULL)
	{
		free(strtab[i]);
		i++;
	}
	free(strtab);
	return (0);
}

int	print_strtab(char **strtab)
{
	int	i;

	i = 0;
	while (strtab[i] != NULL)
	{
		printf("%s\n", strtab[i]);
		i++;
	}
	return (0);
}
