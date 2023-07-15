# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sboulogn <sboulogn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 12:37:04 by sboulogn          #+#    #+#              #
#    Updated: 2023/02/10 12:41:49 by sboulogn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a
HEAD = get_next_line.h
SRCS = get_next_line.c get_next_line_utils.c
			
OBJ = $(SRCS:.c=.o)
CC = gcc
LINK = ar rc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	$(LINK) $(NAME) $(OBJ) $(HEAD)

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
