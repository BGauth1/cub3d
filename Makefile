NAME = cub3d

LIBFT = libft
LFLAGS = -L libft -lft -lm

MLX = MLX42
MFLAGS = $(MLX)/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRC = src/main.c src/color.c src/hooks.c src/map.c src/utils.c src/move.c src/rays.c src/struct_utils.c

ifdef BONUS
	SRC = $(SRC_BONUS)
	NAME = cub3d_bonus
endif

OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Ofast -Wall -Werror -Wextra

CC = clang
all : $(NAME)

$(NAME) : $(OBJ)
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4
	make -C $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(MFLAGS) $(LFLAGS) -o $(NAME)

bonus :
	@make BONUS=1

%.o : %.c
	$(CC) $(FLAGS) -I/src/ -c $< -o $@

clean :
	rm -rf ./$(MLX)/build
	make -C $(LIBFT) clean
	rm -rf $(OBJ) $(OBJBONUS)

fclean : clean
	make -C $(LIBFT) fclean
	rm -rf $(NAME) fractol_bonus

re : fclean all

reb : fclean bonus
