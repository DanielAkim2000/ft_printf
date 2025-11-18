# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/16 17:30:58 by demane            #+#    #+#              #
#    Updated: 2025/11/18 16:31:07 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

SRCS = ft_printf.c ft_char_utils.c ft_format_parser.c ft_hex_utils.c ft_int_utils.c \
	   ft_printf_utils.c ft_ptr_utils.c ft_str_utils.c ft_unsignedint_utils.c		\
	   ft_int_utils2.c ft_args_utils.c

OBJS = $(SRCS:.c=.o)
AR = @ar
RM = @rm -f

all: $(NAME)

bonus: all

$(LIBFT):
	@make --directory=$(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@cp $(LIBFT) $(NAME)
	$(AR) rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make --directory=$(LIBFT_DIR) clean
	$(RM) $(OBJS) $(OBJS_LIBFT)

fclean: clean
	@make --directory=$(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re







