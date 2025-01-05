# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aindjare <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 09:46:09 by aindjare          #+#    #+#              #
#    Updated: 2025/01/04 15:38:28 by aindjare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:=	cc
NAME	:=	cub3d
CFLAGS	:=	-Wall -Wextra -Werror -g -I./mlx/
LDFLAGS	:=	-lm -lz -lXext -lX11
SOURCES	:=	$(wildcard *.c)
OBJECTS	:=	$(SOURCES:%.c=%.o)
DEPS	:=	mlx/libmlx.a mlx/libmlx_Linux.a

all: $(NAME)

$(DEPS):
	$(MAKE) -C mlx

$(NAME): $(OBJECTS) $(DEPS)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(DEPS) $(NAME)

re: fclean all

sanitize: LDFLAGS+=-fsanitize=address
sanitize: re

.PHONY: clean fclean re all
	
.SECONDARY: $(OBJECTS)
