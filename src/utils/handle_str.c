/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfinocie <vfinocie@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:31:29 by thibault          #+#    #+#             */
/*   Updated: 2023/09/16 13:55:02 by vfinocie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	del_whitespace(char **str)
{
	int		begin;
	int		end;
	int		len;
	char	*temp;

	//for (int i = 0; str[i]; i++) {
	//	printf("str[%d] : %s\n", i, str[i]);
	//}

	if (!*str || **str == '\0')
		return (0);
	begin = 0;
	while(str[begin])
	{
		if (!str[begin])
			break;
		return(0);
	}
	begin = 0;
	while (is_whitespace((*str)[begin]))
		begin++;
	end = ft_strlen(*str) -1;
	while(is_whitespace((*str)[end]))
		end--;
	len = end - begin + 1;
	temp = *str;
	*str = ft_substr(temp, begin, len);
	free(temp);
	return (0);
}