#ifndef UTILS_H
# define UTILS_H

/*handle_tab.c*/
int		malloc_strtab(char ***strtab, int nbstr);
int		free_strtab(char **strtab);
int		free_strtab_env(char **strtab);
int		print_strtab(char **strtab);

/*handle_list.c*/
t_tk	*ft_lstlast(t_tk *tk);
int		ft_lstsize(t_tk *tk);
int		print_lst(t_tk *tk);
int		free_env(t_env *env);
int		free_lst(t_tk *head_list);
int		free_elem(t_tk *token);

/*handle_list_add.c*/
t_tk	*ft_lstnew(char *token_str, char **path, char ***envp);
void	ft_lstadd_back(t_tk **head_tk_tk, t_tk *new_tk);
// void	ft_lstadd_front(t_tk **lst, t_tk *new);
// void	ft_lst_add_after(t_tk *current_tk, char *str, char **path, char **envp);
t_tk	*ft_lst_remove(t_tk *current_tk);

/*handle_list_modif.c*/
// void	ft_lst_modif_tk(t_tk *tk, void (*f)(void *));
void	ft_lst_modif_tk_str(t_tk *tk, int (*f)(char **str));
void	ft_lst_modif_tk_type(t_tk *tk, int (*f)(char *str));
void	ft_lst_replace_var(t_tk *tk, int (*f)(char **str, char ***env));
void	ft_lst_classify_tk_unclassified(t_tk *tk);
int 	ft_delete_type_token(t_tk **tk, int tk_type);


/*handle_str.c*/
int		del_whitespace(char **str);

// int		count_variables(char *input);
// char	**get_variables_values(char *input);
// int		replace_with_values(char **input, char **values_tab);

char	*get_var_name_from_input(char *input, int *i);
int		get_var_name_len_from_input(char *input, int i);
char	*find_value_in_tab(char *var_name, char **var_values_tab);
char	*get_value_after_equal(char *var_value);
char	*replace_var_in_string(char *input_str, int *i, char **var_values_tab);
int		replace_with_values(char **input, char ***var_values_tab);
char	*get_var_value(char *input, int *i, char **var_values_tab);

// int		replace_env_variables(char **input, char **env);
int		check_inside_simple_quote(char *input, int index);
#endif