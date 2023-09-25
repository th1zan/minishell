# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibault <thibault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 17:58:32 by ebennace          #+#    #+#              #
#    Updated: 2023/09/25 09:56:23 by thibault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# ==== External folders and libraries ==== #

LIBFT_DIR   = ./src/libft/
LIBFT		= $(LIBFT_DIR)/libft.a

# ==== Project's files ==== #
SRCS       = 		src/thib_minishell.c \
					src/my_function_folder/my_function.c \
					src/check_fct/check_ctrl_op.c \
					src/check_fct/check_group_op.c \
					src/check_fct/check_redir_op.c \
					src/check_fct/check_quotes.c \
					src/check_fct/check_op.c \
					src/check_fct/check_div_op.c \
					src/check_fct/check_token.c \
					src/parsing/input_to_token.c \
					src/parsing/parse_token.c \
					src/parsing/classify_token.c \
					src/parsing/check_parsing_grammar.c \
					src/parsing/check_parsing_token.c \
					src/utils/handle_tab.c \
					src/utils/handle_list.c \
					src/utils/handle_list_add.c \
					src/utils/handle_list_modif.c \
					src/utils/handle_str.c \
					src/built_in/built_in.c \
					src/built_in/is_built_in.c \
					src/execution/redirection.c \
					src/execution/exec.c \
					src/execution/join.c \
#					src/folder_name/file_name.c
#					...


# ==== Source: object files ==== #
OBJS = $(SRCS:.c=.o)

# ==== Template ==== #
TEMPLATE = src/header/minishell_header.txt
# TEMPLATE = 	

# ==== Debug && Leak ==== #
SANITIZE       = -fsanitize=address
LEAKS          = -fsanitize=leak
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
