/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2023/08/31 18:02:41 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_tk
{
	char		*tk_str;	// contenu du token
	int			type;		// type du token 
	char		**env;		// environnement
	int			fd_in;
	int			fd_out;
	struct s_tk	*tk_arg; 	// premier arguments du token (sous-liste)
	struct s_tk	*prev; 		// token suivant
	struct s_tk	*next; 		// token précédent
}	t_tk;
#endif
