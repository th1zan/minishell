#ifndef PARSING_H
# define PARSING_H

/*input_to_word.c*/
int	input_to_token(char *input, t_tk **tk_head);
int	count_words(char *input);

/*parse_token.c*/
int	parse_token(t_tk **tk);
int	del_whitespace(char **str);

#endif