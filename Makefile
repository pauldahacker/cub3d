
BROWN =     \033[38;2;184;143;29m
ORANGE =    \033[38;5;209m
BLUE =      \033[0;94m
DEF_COLOR = \033[0;39m
GREEN =     \033[0;92m
GREY =      \033[38;5;245m

UNAME = $(shell uname)
NAME = cub3d
CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3

ifeq ($(UNAME), Darwin)
MLX_DIR = ./mlx_macOS
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
INCLUDES = -I./headers -Imlx
else ifeq ($(UNAME), Linux)
MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx_Linux.a
MLXFLAGS = -Lmlx -lmlx -lm -L/usr/lib/X11 -lXext -lX11
INCLUDES = -I./headers -I./usr/include -Imlx
endif

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h

HEADER = $(wildcard ./headers/*.h) $(LIBFT_HEADER)

SRCS_DIR = srcs
OBJS_DIR = objs/

SRCS = $(shell find $(SRCS_DIR) -name "*.c")
OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(HEADER)
	@echo "$(BLUE)Linking executable...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(MLXFLAGS) $(LIBFT)
	@echo "$(GREEN)$(NAME) created$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	@echo "$(BROWN)Compiling   ${BLUE}→   $(ORANGE)$< $(DEF_COLOR)"
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
$(OBJS_DIR):
	@mkdir -p $@

$(LIBFT): $(LIBFT_HEADER)
	@echo "$(GREY)Compiling libft$(DEF_COLOR)"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@echo "$(GREY)Compiling mlx$(DEF_COLOR)"
	@$(MAKE) -s -C $(MLX_DIR)
	@echo "$(GREEN)mlx compiled successfully$(DEF_COLOR)"

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(MLX_DIR)/obj
	@echo "$(BROWN)mlx: $(GREEN)removed objects!$(DEF_COLOR)"
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN)All objects removed$(DEF_COLOR)"

fclean: clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "$(GREEN)All binaries removed$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re