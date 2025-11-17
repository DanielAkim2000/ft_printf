# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/16 17:30:58 by demane            #+#    #+#              #
#    Updated: 2025/11/17 15:41:24 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

SRCS = ft_printf.c ft_char_utils.c ft_format_parser.c ft_hex_utils.c ft_int_utils.c \
	   ft_printf_utils.c ft_ptr_utils.c ft_str_utils.c ft_unsignedint_utils.c		\
	   ft_int_utils2.c ft_args_utils.c

OBJS_LIBFT = ft_atoi.o ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o \
	         ft_isascii.o ft_isdigit.o ft_isprint.o ft_itoa.o ft_memchr.o \
	         ft_memcmp.o ft_memcpy.o ft_memmove.o ft_memset.o ft_putchar_fd.o \
	         ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o ft_split.o \
	         ft_strchr.o ft_strdup.o ft_striteri.o ft_strjoin.o ft_strlcat.o \
	         ft_strlcpy.o ft_strlen.o ft_strmapi.o ft_strncmp.o ft_strnstr.o \
	         ft_strrchr.o ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o \
	         ft_intlen.o ft_maxint.o ft_minint.o ft_has_duplicates.o ft_putnbr_base_fd.o \
			 ft_lstlast.o ft_lstdelone.o ft_lstsize.o ft_lstclear.o \
			 ft_lstnew.o ft_lstadd_front.o ft_lstadd_back.o ft_lstiter.o ft_lstmap.o

OBJS = $(SRCS:.c=.o)
AR = @ar
RM = @rm -f

LIBFT = ./libft/libft.a

all: $(NAME)

bonus: all

$(NAME): $(OBJS) $(LIBFT)
	$(AR) x $(LIBFT)
	$(AR) rcs $(NAME) $(OBJS) $(OBJS_LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_LIBFT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re







