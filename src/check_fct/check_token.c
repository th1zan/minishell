/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:16:59 by thibault          #+#    #+#             */
/*   Updated: 2023/08/16 15:30:22 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Name
In the shell command language, a word consisting solely of underscores, digits, and alphabetics from the portable character set. The first character of a name is not a digit.

Portable Filename Character Set
The set of characters from which portable filenames are constructed.

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
a b c d e f g h i j k l m n o p q r s t u v w x y z
0 1 2 3 4 5 6 7 8 9 . _ -
*/

int	is_name(char c)
{
	if (is_portable_filename_char(c) && c != '.')
		return (1);
	return (0);
}

int	is_portable_filename_char(char c)
{
	if (ft_isalnum(c) || c == '.' || c == '_' || c == '-')
		return (1);
	return (0);
}