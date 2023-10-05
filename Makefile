NAME = cub3D

LIBFT = ./includes/libft
LFLAGS = -L $(LIBFT) -lft -lm

MLX = ./includes/MLX42
MFLAGS = $(MLX)/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRC = src/main.c src/draw.c src/hooks.c src/utils.c src/free.c src/move.c src/texture.c src/dda.c src/parsing/ft_parsing.c src/parsing/ft_parsing_color.c src/parsing/ft_parsing_color_error.c src/parsing/ft_parsing_texture.c src/parsing/ft_parsing_texture_error.c src/parsing/ft_init_struct.c src/parsing/ft_parsing_map.c src/parsing/ft_parsing_map_utils.c src/parsing/ft_parsing_map_error.c src/parsing/ft_parse_line_break.c
SRC_DIR = src
SRC_DIR_BONUS = src_bonus

SRC_BONUS = src_bonus/main.c src_bonus/draw.c src_bonus/draw_utils.c src_bonus/hooks.c src_bonus/map.c src_bonus/utils.c src_bonus/free.c src_bonus/move.c src_bonus/rays.c src_bonus/struct_utils.c src_bonus/texture.c src_bonus/dda.c src_bonus/parsing/ft_parsing.c src_bonus/parsing/ft_parsing_color.c src_bonus/parsing/ft_parsing_color_error.c src_bonus/parsing/ft_parsing_texture.c src_bonus/parsing/ft_parsing_texture_error.c src_bonus/parsing/ft_init_struct.c src_bonus/parsing/ft_parsing_map.c src_bonus/parsing/ft_parsing_map_utils.c src_bonus/parsing/ft_parsing_map_error.c

INC_DIR = ./includes/

ifdef BONUS
	SRC = $(SRC_BONUS)
	SRC_DIR = $(SRC_DIR_BONUS)
	NAME = cub3D_bonus
endif

OBJ	= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJ_DIR = obj

OBJBONUS = $(SRC_BONUS:.c=.o)

FLAGS = -Ofast -Wall -Werror -Wextra -g3

CC = clang
all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	@echo "Building MLX..."
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4
	@echo "MLX built."
	@echo "Building Libft..."
	@make -C $(LIBFT)
	@echo "Libft built."
	@echo "Building Cub3D..."
	@$(CC) $(FLAGS) -I $(INC_DIR) $(OBJ) $(MFLAGS) $(LFLAGS) -o $(NAME)
	@echo "Done."

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(FLAGS) -I $(INC_DIR)

bonus :
	@make BONUS=1

%.o : %.c
	$(CC) $(FLAGS) -I/src/ -c $< -o $@

clean :
	rm -rf ./$(MLX)/build
	make -C $(LIBFT) clean
	rm -rf $(OBJ_DIR)

fclean : clean
	make -C $(LIBFT) fclean
	rm -rf $(NAME) cub3D_bonus

re : fclean all

reb : fclean bonus
