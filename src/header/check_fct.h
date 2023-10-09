#ifndef CHECK_FCT_H
# define CHECK_FCT_H

/*check_ctrl_op.c*/
int	is_semicol(char *line, int i);
int	is_amp(char *line, int i);
int	is_double_amp(char *line, int i);
int	is_excl(char *line, int i);
int	is_double_pipe(char *line, int i);

/*check_group_op.c*/
int	is_open_brack(char *line, int i);
int	is_close_brack(char *line, int i);
int	is_open_cbrack(char *line, int i);
int	is_close_cbrack(char *line, int i);

/*check_redir_op.c*/
int	is_redir_out(char *line, int i);
int	is_redir_out_app(char *line, int i);
int	is_redir_in(char *line, int i);
int	is_redir_err(char *line, int i);
int	is_pipe(char *line, int i);

/*check_quotes.c*/
int	is_quote(char *line, int i);
int	is_quoted_char(char *line, int i);
int	is_simple_quote(char *line, int i);
int	is_back_quote(char *line, int i);
int	is_double_quote(char *line, int i);

/*check_op.c*/
int	is_ctrl_op(char *line, int i);
int	is_redir_op(char *line, int i);
int	is_group_op(char *line, int i);
int is_onechar_delim(char *line, int i);
int	is_twochar_delim(char *line, int i);

/*check_div_op.c*/
int	is_hashtag(char *line, int i);
int	is_dollar(char *line, int i);
int	is_inter_mark(char *line, int i);
int	is_here_doc(char *line, int i);
int	is_whitespace(int c);
int	del_whitespace(char **str);

/*check_token.c*/
int	is_name(char c);
int	is_portable_filename_char(char c);
int	is_blank_str(char *str);
int	is_tk_in_out_app(int type);
int	is_tk_redir(int type);

#endif