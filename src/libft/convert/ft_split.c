/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:11:17 by tsanglar          #+#    #+#             */
/*   Updated: 2023/10/12 23:53:47 by thibault         ###   ########.fr       */
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
			//DEBUG
			// if(tab[i])
			// 	ft_printf("tab[%d]: %s, %p\n",i, tab[i], tab[i]);
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
	// ft_printf("ft_split: tab:  %p\n", tab);
	ft_tab(tab, (char *)s, c);
	return (tab);
}



// #include "libft.h"

// static int	count_words(const char *str, char c)
// {
// 	int i;
// 	int trigger;

// 	i = 0;
// 	trigger = 0;
// 	while (*str)
// 	{
// 		if (*str != c && trigger == 0)
// 		{
// 			trigger = 1;
// 			i++;
// 		}
// 		else if (*str == c)
// 			trigger = 0;
// 		str++;
// 	}
// 	return (i);
// }

// static char	*word_dup(const char *str, int start, int finish)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	word = malloc((finish - start + 1) * sizeof(char));
// 	while (start < finish)
// 		word[i++] = str[start++];
// 	word[i] = '\0';
// 	return (word);
// }

// char		**ft_split(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	j;
// 	int		index;
// 	char	**split;

// 	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
// 		return (0);
// 	i = 0;
// 	j = 0;
// 	index = -1;
// 	while (i <= ft_strlen(s))
// 	{
// 		if (s[i] != c && index < 0)
// 			index = i;
// 		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
// 		{
// 			split[j++] = word_dup(s, index, i);
// 			index = -1;
// 		}
// 		i++;
// 	}
// 	split[j] = 0;
// 	return (split);
// }