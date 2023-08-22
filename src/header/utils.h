#ifndef UTILS_H
# define UTILS_H

/*handle_tab.c*/
int		malloc_strtab(char ***strtab, int nbstr);
int		free_strtab(char **strtab);
int		print_strtab(char **strtab);

/*handle_list.c*/
t_tk	*ft_lstlast(t_tk *tk);
int		ft_lstsize(t_tk *tk);
int		print_lst(t_tk *tk);
int		free_lst(t_tk *head_list);
int		free_elem(t_tk *token);

/*handle_list_add.c*/
t_tk	*ft_lstnew(char *token_str);
void	ft_lstadd_back(t_tk **head_tk_tk, t_tk *new_tk);
void	ft_lstadd_front(t_tk **lst, t_tk *new);
void	ft_lst_add_after(t_tk *current_tk, char *str);
t_tk	*ft_lst_remove(t_tk *current_tk);

/*handle_list_modif.c*/
// void	ft_lst_modif_tk(t_tk *tk, void (*f)(void *));
void	ft_lst_modif_tk_str(t_tk *tk, int (*f)(char **str));
void	ft_lst_modif_tk_type(t_tk *tk, int (*f)(char *str));
void	ft_lst_classify_tk_file(t_tk *tk);
#endif