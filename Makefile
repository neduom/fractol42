NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -fsanitize=address -O3 -g -Iincludes


SRCS = mandatory/controls.c mandatory/fractol.c mandatory/handling.c\
		mandatory/julia.c mandatory/mandelbrot.c mandatory/utils.c

OBJS = $(addprefix obj/, $(SRCS:.c=.o))

HEADER = mandatory/fractol.h

MLX_LIB = MLX42/build/libmlx42.a
OS = $(shell uname -s)
NPROC = $(shell nproc)

ifeq ($(OS), Linux)
	LINK = -IMLX42/include -ldl -lglfw -pthread -lm
else
	LINK = -lglfw -ldl -L/Users/$(USER)/.brew/opt/glfw/lib
endif

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LINK) -o $(NAME)

$(MLX_LIB):
	@cmake -S MLX42 -B MLX42/build
	@make -C MLX42/build -j$(NPROC)

obj/mandatory/%.o: mandatory/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
