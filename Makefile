NAME = fractol
NAME_BONUS = fractol_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -O3 -Iincludes


SRCS = mandatory/controls.c mandatory/fractol.c mandatory/handling.c\
		mandatory/julia.c mandatory/mandelbrot.c mandatory/utils.c mandatory/atof.c

SRCSB = bonus/burning_ship.c bonus/controls_bonus.c bonus/fractol_bonus.c \
			bonus/handling_bonus.c bonus/utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)

HEADER = mandatory/fractol.h
HEADER_BONUS = bonus/fractol_bonus.h

MLX_LIB = MLX42/build/libmlx42.a
NPROC = $(shell nproc)

LINK = -IMLX42/include -ldl -lglfw -pthread -lm

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LINK) -o $(NAME)

$(NAME_BONUS): $(OBJSB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJSB) $(MLX_LIB) $(LINK) -o $(NAME_BONUS)

$(MLX_LIB):
	@cmake -S MLX42 -B MLX42/build
	@make -C MLX42/build -j$(NPROC)

mandatory/%.o: mandatory/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJSB)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all
