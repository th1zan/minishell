/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:14:08 by thibault          #+#    #+#             */
/*   Updated: 2023/08/07 11:46:49 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{

	ft_coucou();
	
	/*fonction ft_example se trouve dans my_function_folder/my_function.c,
	son prototype est dans my_header_for_my_function.h*/

	ft_example();
	

	return(0);

}

int	ft_coucou(void)
{
	ft_printf("Coucou depuis le fichier minishell.c !\net ...\n");
	return (0);
}