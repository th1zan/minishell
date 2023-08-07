/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:31:26 by tsanglar          #+#    #+#             */
/*   Updated: 2023/08/07 08:49:17 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*source;
	char	*destination;
	int		n_oct;
	int		i;

	source = (char *)src;
	destination = (char *)dest;
	n_oct = (int)n;
	i = 0;
	if (source == 0 && destination == 0)
		return (dest);
	while (i < n_oct)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}
