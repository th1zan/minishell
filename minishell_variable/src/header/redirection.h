/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:14:55 by thibault          #+#    #+#             */
/*   Updated: 2024/01/31 11:00:23 by zsoltani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

/*get_operator_tk.c*/
t_tk	*get_next_input_operator_tk(t_tk *tk);
t_tk	*get_prev_input_operator_tk(t_tk *tk);
t_tk	*get_next_output_operator_tk(t_tk *tk);
t_tk	*get_prev_output_operator_tk(t_tk *tk);

/*redir_operator_fd.c*/
int		handle_dup2_input_error(int fd_in);
int		handle_dup2_output_error(int fd_out);
int		redirect_input(t_tk *token);
int		redirect_output(t_tk *token);
int		process_redirection(t_tk *token);

/*redirection.c*/
int		set_redirection(t_tk **tk);
int		redir_operator_fd(t_tk **tk);

/*set_cmd_fd_1.c*/
int		set_cmd_std_fd(t_tk **tk);
int		set_cmd_pipe_fd(t_tk **tk);
int		chevron_out_between_pipe_and_cmd(t_tk *start, t_tk *end);
int		chevron_in_between_pipe_and_cmd(t_tk *start, t_tk *end);

/*set_cmd_fd_2.c*/
void	set_fd_in(t_tk *tmp);
void	set_fd_out(t_tk *tmp);
int		set_cmd_operator_fd(t_tk **tk);

/*set_operator_fd.c*/
int		set_default_fd(t_tk **tk);
int		open_chevron_fd(t_tk *tmp, int flags);
int		set_input_operator_fd(t_tk **tk);
int		set_output_operator_fd(t_tk **tk);
int		open_file_to_fd(char *file, int option);

/*set_pipe_fd.c*/
int		set_pipe_fd(t_tk **tk);
int		duplicate_fd(int old_fd, int new_fd, char *error_message);
int		handle_pipes(t_tk *tk);
int		set_fd_for_pipe(t_tk *tk);

#endif
