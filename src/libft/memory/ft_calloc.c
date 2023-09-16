/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfinocie <vfinocie@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:51:13 by tsanglar          #+#    #+#             */
/*   Updated: 2023/09/16 12:43:52 by vfinocie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size) // 4, 5
{
	char	*p;
	size_t	i;

	p = (void *) malloc(size * count); //malloc de 20
	if (!p)
		return (NULL);
	i = 0;
	while (i < size * count)
	{	
		p[i] = 0;
		i++;
	}
	return ((void *) p);
}
