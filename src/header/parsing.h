#ifndef PARSING_H
# define PARSING_H

/*input_to_word.c*/
int		*get_delimiter(char *input);
int		input_to_token(char *input, char ***envp, t_tk **tk_head, int *delimiter);
int		count_words(char *input);

/*parse_token.c*/
int		parse_token(t_tk **tk);
int		check_parsing(t_tk *tk);
int		classify_operator(char *str);
int		delete_quotes(char **str);
int 	handle_quotes(t_tk *head_tk);

char	*remove_quotes(char *str);
char	*copy_without_quotes(char *str, int len, int *quote_positions, int num_quotes);


/*check_parsing_grammar.c*/
int		check_first_last_token(t_tk *first, t_tk *last);
int		check_main_list_tokens(t_tk *tk);
int		check_redir_sublist(t_tk *tk);
int		check_here_doc_sublist(t_tk *tk);
int		check_cmd_sublist(t_tk *tk);
int		check_grammar(t_tk *tk);

/*check_parsing_token.c*/
int		check_cmd(t_tk *tk);
int		test_cmd(t_tk *tk);
int		check_access(char *cmd);
int		check_input_file(t_tk *tk);

/*classify_token.c*/
int		classify_token(char *str);
int		ft_handle_hd_arg_tk(t_tk *tk);
int		ft_handle_arg_tk(t_tk *tk);
int		ft_handle_file_tk(t_tk *tk);
int		ft_handle_built_in(t_tk *tk);
void	move_arg_to_sublist(t_tk **tmp, t_tk **sublst_last, t_tk *cmd, t_tk **last_non_arg);
t_tk	*move_args_to_sublist(t_tk *tk);
#endif