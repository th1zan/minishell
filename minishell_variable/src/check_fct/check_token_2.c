/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:33:47 by thibault          #+#    #+#             */
/*   Updated: 2023/11/03 10:35:30 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	classify_operator(char *str)
{
	if (*str == '\0')
		return (TK_NULL);
	if (is_blank_str(str))
		return (TK_BLANK);
	if (is_here_doc(str, 0))
		return (TK_HERE_DOC);
	if (is_redir_out_app(str, 0))
		return (TK_APP_CHEVRON);
	if (is_redir_in(str, 0))
		return (TK_IN_CHEVRON);
	if (is_redir_out(str, 0))
		return (TK_OUT_CHEVRON);
	if (is_pipe(str, 0))
		return (TK_PIPE);
	if (is_onechar_delim(str, 0) || is_twochar_delim(str, 0))
		return (-2);
	return (TK_UNCLASSIFIED);
}
