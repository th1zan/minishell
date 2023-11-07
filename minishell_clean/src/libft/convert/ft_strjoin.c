/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:37:01 by tsanglar          #+#    #+#             */
/*   Updated: 2023/08/07 08:48:16 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		ls1;
	int		ls2;
	int		i;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	s3 = malloc((sizeof(char) * (ls1 + ls2 + 1)));
	if (!s3)
		return (0);
	i = 0;
	while (i < ls1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (i < ls1 + ls2)
	{
		s3[i] = s2[i - ls1];
		i++;
	}
	s3[i] = 0;
	return (s3);
}
