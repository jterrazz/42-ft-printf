# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterrazz <jterrazz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/12 15:20:52 by jterrazz          #+#    #+#              #
#    Updated: 2017/06/04 10:50:21 by jterrazz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_PATH = ./src

SRC_NAME = ft_printf.c \
		   dispatch.c flags.c \
		   ft_itoa_base.c ft_memalloc.c ft_putchar.c ft_putchar_fd.c \
		   ft_putstr.c ft_putstr_fd.c ft_strdup.c ft_strjoin.c ft_strlen.c \
		   ft_strnew.c render_char.c render_hex.c render_nbr.c \
		   ft_uitoa_base.c ft_atoi.c ft_memset.c ft_strsub.c \
		   render_octal.c render_pointer.c render_str.c render_unsigned.c \
		   get_uintmax.c get_intmax.c display.c checker.c render_double.c \
		   flags_init.c conv_init.c


SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OFILES = $(SRC_NAME:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)
	@echo "Compilation:\033[92m OK\033[0m"

%.o: $(SRC_PATH)/%.c
	$(CC) -c $(CFLAGS) -o $@ $< -I includes

clean:
	@rm -rf $(OFILES)
	@echo "Deleting:\n\033[33m $(OFILES)\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "Deleting:\n\033[33m $(NAME)\033[0m"

re : fclean all

.PHONY: all clean fclean re
