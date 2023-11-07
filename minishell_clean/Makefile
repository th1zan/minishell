# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibault <thibault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 17:58:32 by ebennace          #+#    #+#              #
#    Updated: 2023/11/07 21:14:51 by thibault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# ==== External folders and libraries ==== #

LIBFT_DIR   = ./src/libft/
LIBFT		= $(LIBFT_DIR)/libft.a

# ==== Project's files ==== #
SRCS       = 		src/minishell.c \
					src/check_fct/check_ctrl_op.c \
					src/check_fct/check_group_op.c \
					src/check_fct/check_redir_op.c \
					src/check_fct/check_quotes.c \
					src/check_fct/check_op.c \
					src/check_fct/check_div_op.c \
					src/check_fct/check_token_1.c \
					src/check_fct/check_token_2.c \
					src/parsing/input_to_token_1.c \
					src/parsing/input_to_token_2.c \
					src/parsing/parse_token_1.c \
					src/parsing/parse_token_2.c \
					src/parsing/classify_token_1.c \
					src/parsing/classify_token_2.c \
					src/parsing/classify_token_3.c \
					src/parsing/check_parsing_gramm_utils_1.c \
					src/parsing/check_parsing_gramm_utils_2.c \
					src/parsing/check_parsing_grammar.c \
					src/parsing/check_parsing_token_1.c \
					src/parsing/check_parsing_token_2.c \
					src/utils/handle_tab.c \
					src/utils/handle_list.c \
					src/utils/handle_list_add.c \
					src/utils/handle_list_modif.c \
					src/utils/handle_str.c \
					src/utils/get_tk.c \
					src/utils/free_lst.c \
					src/utils/handle_var_utils_1.c \
					src/utils/handle_var_utils_2.c \
					src/utils/handle_variable.c \
					src/utils/classify_token.c \
					src/utils/print_lst.c \
					src/built_in/built_in_env_pwd.c \
					src/built_in/built_in_export_1.c \
					src/built_in/built_in_export_2.c \
					src/built_in/built_in_unset.c \
					src/built_in/built_in_echo.c \
					src/built_in/built_in_exit.c \
					src/built_in/built_in_cd.c \
					src/built_in/is_built_in_1.c \
					src/built_in/is_built_in_2.c \
					src/redirection/redirection.c \
					src/redirection/set_pipe_fd.c \
					src/redirection/redir_operator_fd.c \
					src/redirection/set_cmd_fd.c \
					src/redirection/set_operator_fd.c \
					src/redirection/get_operator_tk.c \
					src/execution/execution.c \
					src/execution/wait_and_close.c \
					src/execution/status.c \
					src/execution/handle_cmd.c \
				
					

# ==== Source: object files ==== #
OBJS = $(SRCS:.c=.o)

# ==== Template ==== #
TEMPLATE = src/header/minishell_header.txt
# TEMPLATE = 	

# ==== Debug && Leak ==== #
# SANITIZE       = -fsanitize=address
# LEAKS          = -fsanitize=leak
SANITIZE       = 
LEAKS       = 


DEBUGGER       = lldb

# ==== Remove ==== #
RM_FILE = /bin/rm -rf

# ==== Compiling ==== #
CC              ?= gcc
FLAGS           = -g3
FLAGS           += -Wall -Werror -Wextra
FLAGS           += $(SANITIZE)
FLAGS           += -I$(HOME)/.brew/opt/readline/include
READLINE		= -lreadline
READLINE		+= -L$(HOME)/.brew/opt/readline/lib
MAKE            = make -s

# === Convert all .c to .o with flags and header === # 
all: $(NAME)

${OBJS}: %.o: %.c
	@echo "...Compiling $<"
	@$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@echo "==== Compiling libft ===="
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "==== Compiling $(NAME) ===="
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE) 
	@echo "==== $(NAME) is ready! ===="
	@cat "$(TEMPLATE)"

ENTITLEMENTS = entitlements.plist

sign: $(NAME)
	@echo "==== Signing $(NAME) for profiling ===="
	@echo '<?xml version="1.0" encoding="UTF-8"?>' > $(ENTITLEMENTS)
	@echo '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "https://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> $(ENTITLEMENTS)
	@echo '<plist version="1.0">' >> $(ENTITLEMENTS)
	@echo '    <dict>' >> $(ENTITLEMENTS)
	@echo '        <key>com.apple.security.get-task-allow</key>' >> $(ENTITLEMENTS)
	@echo '        <true/>' >> $(ENTITLEMENTS)
	@echo '    </dict>' >> $(ENTITLEMENTS)
	@echo '</plist>' >> $(ENTITLEMENTS)
	@codesign -s - -v -f --entitlements $(ENTITLEMENTS) $(NAME)
	@rm -f $(ENTITLEMENTS)


clean:
	@echo "==== Cleaning all LIBFT .o files ===="
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "==== Cleaning all MINISHELL .o files ===="
	@$(RM_FILE) $(OBJS)

fclean: clean
	@echo "==== Full cleaning LIBFT ===="
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "==== Full cleaning $(NAME) ===="
	@$(RM_FILE) $(NAME)

debug : $(OBJS)
	@echo "==== Debug mode ===="
	@$(CC) $(OBJS) $(FLAGS) $(READLINE) $(SANITIZE) $(LIBFT) -o $(NAME)
	$(DEBUGGER) $(NAME)
	@cat "$(TEMPLATE)"

sanitize :	$(OBJS)
	@echo "==== Sanitize mode ===="
	@$(CC) $(OBJS) $(FLAGS) $(READLINE) $(SANITIZE) $(LIBFT) -o $(NAME)
	@cat "$(TEMPLATE)"

leak :	$(OBJS)
		@echo "==== Leaks mode ===="
		@$(CC) $(OBJS) $(FLAGS) $(READLINE) $(LEAKS) $(LIBFT) -o $(NAME)
		@cat "$(TEMPLATE)"

re: fclean all

.PHONY: all clean fclean debug sanitize leak re
