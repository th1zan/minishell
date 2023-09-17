/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfinocie <vfinocie@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2023/09/16 14:03:55 by vfinocie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_tk
{
	char		*tk_str;	// contenu du token, built in input_to_token, cleaned in parse_token
	int			type;		// type du token 
	char		**env;		// environnement
	int			fd_in;
	int			fd_out;
	struct s_tk	*tk_arg; 	// premier arguments du token (sous-liste)
	struct s_tk	*prev; 		// token suivant
	struct s_tk	*next; 		// token précédent
}	t_tk;
#endif
