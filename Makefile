# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: demane <emanedanielakim@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/16 17:30:58 by demane            #+#    #+#              #
#    Updated: 2025/11/16 18:37:32 by demane           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft

SRCS = ft_printf.c
OBJS = $(SRCS:.c=.o)
AR = ar
RM = rm -f

LIBFT = ./libft/libft.a

all: $(NAME)

bonus: all

$(NAME): $(OBJS) $(LIBFT)
	# Crée l'archive avec ft_printf.o
	$(AR) rcs $(NAME) $(OBJS)
	# Ajoute tous les .o de libft.a dedans
	@ar x $(LIBFT)
	@ar rcs $(NAME) *.o
	@rm -f *.o  # nettoie les .o extraits

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re







