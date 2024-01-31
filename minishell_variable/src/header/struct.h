/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 09:31:25 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 22:46:48 by zsoltani         ###   lausanne.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//faire un make re si on ajoute une variable !!

typedef struct s_env	t_env;

typedef struct s_tk
{
	char		*tk_str;
	int			type;
	char		***env;
	int			fd_in;
	int			fd_out;
	int			pid;
	char		**path_tab;
	char		*path;
	int			is_var_type_with_space_before;
	t_env		*env_struct;
	struct s_tk	*tk_arg;
	struct s_tk	*prev;
	struct s_tk	*next;
}	t_tk;

typedef struct s_env
{
	t_tk	*tk_head;
	char	**env_main;
	char	**path_tab;
	char	*minishell_directory;
	int		error_parsing;
	int		error_processing;
	int		status;
}	t_env;
#endif
