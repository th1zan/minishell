/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:15:38 by tsanglar          #+#    #+#             */
/*   Updated: 2023/10/13 13:42:05 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	// s = input = "ls | wc"
	// start = begin = 0
	// len = len = 3;
	char	*substr;
	size_t	i;
	size_t	slen;

	slen = 0;
	while (s[slen])// used to set slen to the size of s / input
		slen++;
	// here slen = 7
	if (start > slen) // 0 > 7
		len = 0;
	if (len > slen - start) // 3 > 7 - 0
		len = slen - start;
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	i = 0;
	while (i < len && start + i < slen) // 1 < 1 && 0 + i < 7
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
	// return = "ls \0";
}
