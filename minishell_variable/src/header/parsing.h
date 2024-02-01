/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:00:32 by thibault          #+#    #+#             */
/*   Updated: 2024/01/31 11:05:37 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*check_parsing_gramm_utils_1.c*/
int		check_first_last_token(t_tk *first, t_tk *last, t_env *env);
void	report_syntax_error(t_env *env, char *token);
int		check_cmd_after_pipe(t_tk *tk);

/*check_parsing_gramm_utils_2.c*/
int		check_here_doc_arg(t_tk *tk);
int		check_main_list_tokens(t_tk *tk);
int		check_redir_sublist(t_tk *tk);

/*check_parsing_grammar.c*/
int		prt_err(t_env *env, char *message, int status, int return_value);
int		check_input_redirect(t_tk *tmp);
int		check_output_redirect(t_tk *tmp);
int		validate_tokens(t_tk *tk);
int		check_grammar(t_env *env);

/*check_parsing_token_1.c*/
int		check_input_file(t_tk *tk, t_env *env);
int		check_cmd(t_tk *tk);
void	cmd_err(int status, char *cmd);

/*check_parsing_token_2.c*/
int		try_paths(t_env *env, char **path_tab, char *cmd);
int		test_cmd(t_tk *tk);
int		check_access(t_env *env, char *cmd);

/*classify_token_1.c*/
void	mv_arg_to_sublst(t_tk **tmp, t_tk **sub_last, t_tk *cmd, t_tk **last);
t_tk	*handle_command(t_tk **cmd, t_tk **tmp, t_tk **last, t_tk **sub_last);
t_tk	*move_args_to_sublist(t_tk *tk);

/*classify_token_2.c*/
int		ft_handle_arg_tk(t_tk *tk);
int		open_temp_file(t_tk *tk, char **temp_file_path);
int		write_to_temp_file(int fd, char *input);
void	free_memory_and_close_fd(int *fd, char **file_path);
int		process_hd_arg(t_tk *tk, char **temp_file_path);

/*classify_token_3.c*/
int		ft_handle_hd_arg_tk(t_tk *tk);
int		ft_handle_file_tk(t_tk *tk);
int		ft_handle_built_in(t_tk *tk);

/*input_to_token_1.c*/
void	handle_delimiter_quotes(char *input, int *i);
void	process_character(char *input, int *delimiter, int *i);
void	process_special_delimiters(char *input, int *delim, int *i, int len);
void	initialize_delimiters(char *input, int *delimiter);

/*input_to_token_2.c*/
int		*get_delimiter(char *input);
int		add_token(char *input, int begin, int len, t_tk **tk, t_env *env);
int		input_to_token(char *input, t_tk **tk, int *delimiter, t_env *env);

/*parse_token_1.c*/
int		parse_token(t_tk **head_tk, t_env *env);
int		check_parsing(t_env *env);
int		handle_quotes(t_tk *head_tk);

/*parse_token_2.c*/
char	*copy_and_skip_quotes(char *str, char quote);
int		remove_quotes_loop(char **final_str, int *i);
char	*remove_quotes(char *str);
#endif
