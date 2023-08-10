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

/*handle_list_add.c*/
t_tk	*ft_lstnew(char *token_str);
void	ft_lstadd_back(t_tk **head_tk_tk, t_tk *new_tk);
void	ft_lstadd_front(t_tk **lst, t_tk *new);
void	ft_lst_add_betw(t_tk *prev_tk, t_tk *next_tk, char *str);

#endif