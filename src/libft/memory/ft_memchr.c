/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:28:34 by tsanglar          #+#    #+#             */
/*   Updated: 2023/08/07 08:49:10 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{	
	while (!s || n--)
	{
		if (*(unsigned char *)s == (unsigned char) c)
			return ((void *) s);
		s++;
	}
	return (0);
}
