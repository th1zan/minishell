/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:11:17 by tsanglar          #+#    #+#             */
/*   Updated: 2023/11/07 21:22:23 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_indexfin(char *init, char c );
int		ft_nbline(char *s, char c);
void	ft_strcpy(char *dst, char *init, char *fin);

void	ft_strcpy(char *dst, char *init, char *fin)
{
	while (init < fin)
		*(dst++) = *(init++);
	*dst = 0;
}

int	ft_nbline(char *s, char c)
{
	int	nbli;

	nbli = 0;
	while (*s)
	{
		if (*s != c)
		{
			nbli++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (nbli);
}

void	ft_tab(char **tab, char *s, char c)
{
	char	*init;
	int		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			init = (char *) s;
			while (*s != c && *s)
				s++;
			tab[i] = (char *)malloc((char *)s - init + 1);
			if (!tab[i])
				return ;
			ft_strcpy(tab[i], init, (char *) s);
			i++;
		}
		else
			s++;
	}
	tab[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	int		nbli;	
	char	**tab;

	if (!s)
		return (0);
	nbli = ft_nbline((char *)s, c);
	tab = (char **)malloc(sizeof(char *) * (nbli + 1));
	if (!tab)
		return (0);
	ft_tab(tab, (char *)s, c);
	return (tab);
}
