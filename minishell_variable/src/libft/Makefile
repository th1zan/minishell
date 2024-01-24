# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thibault <thibault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 16:33:11 by tsanglar          #+#    #+#              #
#    Updated: 2023/08/07 10:04:30 by thibault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the librairy
NAME = libft.a

# Source: files
SRCS = check/ft_isalpha.c \
			check/ft_isdigit.c \
			check/ft_isalnum.c \
			check/ft_isascii.c \
			check/ft_isprint.c \
			check/ft_strlen.c \
			check/ft_strlcat.c \
			check/ft_strchr.c \
			check/ft_strrchr.c \
			check/ft_strncmp.c \
			check/ft_strnstr.c \
			check/ft_strtrim.c \
			convert/ft_toupper.c \
			convert/ft_tolower.c \
			convert/ft_strlcpy.c \
			convert/ft_strdup.c \
			convert/ft_substr.c \
			convert/ft_strjoin.c \
			convert/ft_split.c \
			convert/ft_itoa.c\
			convert/ft_strmapi.c \
			convert/ft_striteri.c \
			convert/ft_atoi.c \
			memory/ft_memset.c \
			memory/ft_bzero.c \
			memory/ft_memcpy.c \
			memory/ft_memmove.c \
			memory/ft_memchr.c \
			memory/ft_memcmp.c \
			memory/ft_calloc.c \
			print/ft_putchar_fd.c \
			print/ft_putstr_fd.c \
			print/ft_putendl_fd.c \
			print/ft_putnbr_fd.c \
			getnextline/get_next_line.c \
			ft_printf/ft_print_csdiu.c \
			ft_printf/ft_print_hex.c \
			ft_printf/ft_printf.c \
			ft_printf/ft_printptr.c \

# Source: object files
OBJS = $(SRCS:.c=.o)

# Compiling flags
FLAGS = -Wall -Wextra -Werror -I.

# all rule ("make all" ou "make" execute cette commande -> les dépendances obj et NAME sont construites)
all: ${NAME}

# Compiling -> construction des fichiers obj
$(OBJS): %.o: %.c
	@echo "...Compiling $<"
	@gcc $(FLAGS) -o $@ -c $<
	
# Linking
${NAME}: ${OBJS}
	@echo "Wait a sec..."
	@echo "Object files generated."
	@echo "Linking $@"
	@ar src $(NAME) $(OBJS)
	@echo "$(NAME) generated!".

# clean rule
clean:
	@rm -Rf $(OBJS)
	@echo "Objects removed!"

# fclean rule
fclean:	clean
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

# re rule
re:	fclean all

# phony
.PHONY: all clean fclean re
