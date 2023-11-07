/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:19:19 by tsanglar          #+#    #+#             */
/*   Updated: 2023/11/07 21:21:48 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_strtriminit(char const *s1, char const *set);
int		ft_strtrimfin(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		ixinit;
	int		ixfin;
	char	*strim;
	int		i;

	ixinit = ft_strtriminit(s1, set);
	ixfin = ft_strtrimfin(s1, set);
	if (ixinit > ixfin)
		ixfin = ixinit;
	strim = (char *)malloc((sizeof(char) * (ixfin - ixinit + 1)));
	if (strim == NULL)
		return (NULL);
	i = 0;
	while (i < ixfin - ixinit)
	{
		strim[i] = s1[ixinit + i];
		i++;
	}
	strim[i] = 0;
	return (strim);
}

int	ft_strtriminit(char const *si, char const *set)
{
	int		ixinit;
	int		j;

	ixinit = 0;
	j = 0;
	while (set[j] != 0 && ixinit <= (int)ft_strlen(si))
	{
		if (si[ixinit] == set[j])
		{
			ixinit++;
			j = 0;
		}
		else
			j++;
	}
	return (ixinit);
}

int	ft_strtrimfin(char const *sf, char const *set)
{
	int		ixfin;
	int		j;

	ixfin = ft_strlen(sf) - 1;
	j = 0;
	while (set[j] != 0 && ixfin >= 0)
	{
		if (sf[ixfin] == set[j])
		{
			ixfin--;
			j = 0;
		}
		else
			j++;
	}
	ixfin++;
	return (ixfin);
}
