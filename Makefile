NAME	:= Game
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= /Users/$$USER/Desktop/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= get_next_line/gnl.a Libft/libft.a
SRCS	:= main.c map_parsing.c map_parsing2.c utils.c verif_map.c err.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

# libmlx:
# 	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(MAKE) -C Libft
	$(MAKE) -C get_next_line
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	$(MAKE) clean -C Libft
	$(MAKE) clean -C get_next_line
	@rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C Libft
	$(MAKE) fclean -C get_next_line
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx