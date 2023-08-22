#ifndef PARSING_H
# define PARSING_H

/*input_to_word.c*/
int	*get_delimiter(char *input);
int		input_to_token(char *input, t_tk **tk_head, int *delimiter);
int		count_words(char *input);

/*parse_token.c*/
int		parse_token(t_tk **tk);
int 	ft_delete_type_token(t_tk **tk, int tk_type);
int		check_file_operator(int type);
int		ft_handle_file_tk(t_tk *tk);
int		ft_handle_hd_arg_tk(t_tk *tk);
int		ft_handle_arg_tk(t_tk *tk);
int		del_whitespace(char **str);
int		classify_operator(char *str);
int		classify_token(char *str);

#endif