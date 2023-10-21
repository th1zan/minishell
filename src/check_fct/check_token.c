/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:16:59 by thibault          #+#    #+#             */
/*   Updated: 2023/10/18 16:58:08 by thibault         ###   ########.fr       */
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
	if (is_portable_filename_char(c)) //&& c != '.')
		return (1);
	return (0);
}

int	is_portable_filename_char(char c)
{
	if (ft_isalnum(c) || c == '.' || c == '_' || c == '-')
		return (1);
	return (0);
}

int	is_blank_str(char *str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		if (!is_whitespace(str[i]))
			return (0);
		str++;
	}
	return (1);
}

int	is_tk_in_out_app(int type)
{
	if (type == TK_APP_CHEVRON)
		return (1);
	else if (type == TK_IN_CHEVRON)
		return (1);
	else if (type == TK_OUT_CHEVRON)
		return (1);
	return (0);
}

int	is_tk_redir(int type)
{
	if (type == TK_APP_CHEVRON)
		return (1);
	else if (type == TK_IN_CHEVRON)
		return (1);
	else if (type == TK_OUT_CHEVRON)
		return (1);
	else if (type == TK_HERE_DOC)
		return (1);
	return (0);
}

int	classify_operator(char *str)
{
	if (*str == '\0')
		return (TK_NULL);
	if(is_blank_str(str))
		return(TK_BLANK);
	if(is_here_doc(str, 0))
		return(TK_HERE_DOC);
	if(is_redir_out_app(str, 0))
		return(TK_APP_CHEVRON);
	if(is_redir_in(str, 0))
		return(TK_IN_CHEVRON);
	if(is_redir_out(str, 0))
		return(TK_OUT_CHEVRON);
	if(is_pipe(str, 0))
		return(TK_PIPE);
	// Error to handle if unhandled token
	if(is_onechar_delim(str, 0) || is_twochar_delim(str, 0))
		return(-2);
	return (TK_UNCLASSIFIED);
}

