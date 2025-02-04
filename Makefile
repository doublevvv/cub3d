# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 10:25:40 by vlaggoun          #+#    #+#              #
#    Updated: 2025/02/03 10:10:34 by vlaggoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

HEADER = cub3d.h

SOURCES = main.c getnextline/get_next_line.c getnextline/get_next_line_utils.c recover_data.c srcs/initialization.c srcs/parsing.c srcs/utils.c \
free.c getnextline/ft_strncmp.c getnextline/ft_substr.c

SRCS = $(addprefix $(OBJ_DIR)/, $(SOURCES))

OBJ_DIR = objs

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g3

RM = rm -rf

all: $(NAME)
# enleve les @ pour que le makefile re-print
$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) $(OBJ_DIR)

re: fclean
	@make all

.PHONY: all clean fclean re
