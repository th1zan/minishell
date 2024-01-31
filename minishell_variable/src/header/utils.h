/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:29:09 by thibault          #+#    #+#             */
/*   Updated: 2024/01/30 22:50:04 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*classify_token.c*/
void	classify_token_operator(t_tk *tmp);
void	classify_token_type(t_tk *tk);
void	ft_lst_classify_tk_unclassified(t_tk *tk);

/*free_lst.c*/
// int		free_env(t_env *env);
int		free_env(t_env *env);
int		free_lst(t_tk *head_list);
int		free_elem(t_tk *token);

/*get_tk.c*/
t_tk	*get_next_cmd(t_tk *tk);
t_tk	*get_next_type_tk(t_tk *tk, int type);
t_tk	*get_prev_type_tk(t_tk *tk, int type);
t_tk	*get_prev_pipe_tk(t_tk *tk);
t_tk	*get_next_pipe_tk(t_tk *tk);

/*handle_list_add.c*/
t_tk	*ft_lstnew(char *token_str);
void	ft_lstadd_back(t_tk **head_tk_tk, t_tk *new_tk);
t_tk	*ft_lst_remove(t_tk *current_tk);

/*handle_list_modif.c*/
void	ft_lst_modif_tk_str(t_tk *tk, int (*f)(char **str));
void	ft_lst_modif_tk_type(t_tk *tk, int (*f)(char *str));
void	ft_lst_replace_var(t_tk *tk, int (*f)(char **str, t_tk *tk_repl));
int		ft_delete_type_token(t_tk **tk, int tk_type);

/*handle_list.c*/
t_tk	*ft_lstlast(t_tk *tk);
t_tk	*ft_lstfirst(t_tk *tk);
int		ft_lstsize(t_tk *tk);

/*handle_str.c*/
int		del_whitespace(char **str);
char	*get_var_value(char *input, int *i, char **var_values_tab);

/*handle_tab.c*/
int		malloc_strtab(char ***strtab, int nbstr);
int		free_strtab(char **strtab);
int		free_strtab_env(char **strtab);
int		print_strtab(char **strtab, int fd_out);

/*handle_var_utils_1.c*/
char	*get_var_name_from_input(char *input, int *i);
int		get_var_name_len_from_input(char *input, int i);
char	*find_value_in_tab(char *var_name, char **var_values_tab);
char	*get_value_after_equal(char *var_value);

/*handle_var_utils_2.c*/
int		check_inside_simple_quote(char *input, int index);
char	*replace_var_status_in_string(char *input_str, int *i, char *var_value);
char	*str_with_valu(char *begin, char *var_value, char *input, int *tab_pos);
char	*replace_var_in_str(char *input_str, int *i, char **env);

/*handle_variable.c*/
int		update_input_if_needed(char **input, char *new_input);
char	*handle_status_variable(char *input, int *i, t_env *env);
char	*expand_var(char *input, int *i, char **var_val_tab, t_env *env);
void	process_input(char **input, int *i, t_tk *env, int *is_var);
int		replace_with_values(char **input, t_tk *tk);

//A SUPPRIMER car pas à la norme
int		print_lst(t_tk *tk);
#endif
