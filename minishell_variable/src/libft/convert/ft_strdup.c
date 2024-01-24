/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:45:33 by tsanglar          #+#    #+#             */
/*   Updated: 2023/11/06 11:36:45 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s1)
{
	char		*c;
	size_t		slen;	
	size_t		i;

	slen = 0;
	while (s1[slen])
		slen++;
	c = (char *) malloc(sizeof(char) * slen + 1);
	if (!c)
		return (0);
	i = 0;
	while (i < sizeof(char) * slen)
	{
		c[i] = s1[i];
		i++;
	}
	c[i] = 0;
	return (c);
}
