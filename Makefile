# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 16:39:49 by simarcha          #+#    #+#              #
#    Updated: 2024/11/15 21:19:48 by simarcha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#This Makefile works only on Linux. It won't work on MacOS nor Windows.
#SETUP
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra #-fsanitize=address
NAME				= cub3d
RM					= rm -rf

#FILES AND PATHS
#HEADER
INCLUDE_DIR			= headers/
INCLUDE_FILES		= colors.h \
					cub3d.h \
					parsing.h \
					raycasting.h \
					textures.h
INCLUDE				= $(addprefix $(INCLUDE_DIR), $(INCLUDE_FILES))

#SRCS - Where the main files for this project are located
SRCS_DIR			= srcs/
SRCS_FILES			= main.c \
					colors/colors.c \
					controls/controls.c \
					controls/movement_utils.c \
					controls/movement.c \
					controls/rotation.c \
					minimap/minimap_utils.c \
					minimap/minimap.c \
					parsing/checking.c \
					parsing/gnl2.c \
					parsing/map_parsing_utils.c \
					parsing/map_parsing.c \
					parsing/parsing_utils.c \
					parsing/parsing.c \
					raycasting/calculate_best_distance.c \
					raycasting/draw_textures.c \
					raycasting/drawing_raycasting.c \
					raycasting/horizontal_intersection.c \
					raycasting/raycasting_utils.c \
					raycasting/vertical_intersection.c \
					raycasting/checking_calculating_next_point.c

SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJ_SRCS			= $(SRCS:.c=.o)

#MINILIB
MINILIB_DIR			= mlx/
MINILIB_ARCHIVE		= $(addprefix $(MINILIB_DIR), libmlx.a)
MINILIB_FLAGS		= -Lmlx -lmlx -lm -L/usr/lib/X11 -lXext -lX11

#LIBFT 
LIBFT_DIR			= libft/
LIBFT_ARCHIVE		= $(addprefix $(LIBFT_DIR), libft.a)

#RULES AND COMMANDS
all:				$(LIBFT_ARCHIVE) $(MINILIB_ARCHIVE) $(NAME)

%.o:				%.c Makefile $(INCLUDE)
					@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(MINILIB_DIR) -c $< -o $@

$(NAME):			$(OBJ_SRCS) $(LIBFT_ARCHIVE) Makefile
					@$(CC) $(CFLAGS) $(OBJ_SRCS) -L$(LIBFT_DIR) -lft $(MINILIB_FLAGS) $(MINILIB_ARCHIVE) -o $(NAME)
					@echo "\033[1;32mReady to play!\033[0m"

$(LIBFT_ARCHIVE):
					@$(MAKE) -s -C $(LIBFT_DIR)
#					@echo "Compiled $(LIBFT_ARCHIVE)."

$(MINILIB_ARCHIVE):
					@$(MAKE) -s -C $(MINILIB_DIR)
					@echo "\033[1;35mCompiled $(MINILIB_ARCHIVE).\033[0m"
					@echo "\033[1;37mWait few seconds\033[0m"

clean:
					@echo "\033[1;31m\033[1mDeleting every object files\033[0m" 
					@echo "\033[1mCleaning the object srcs files\033[0m"
					$(RM) $(OBJ_SRCS)
					@echo ""
					@echo "\033[1mCleaning the object libft files\033[0m"
					@$(MAKE) clean -C $(LIBFT_DIR)
					@echo ""
					@echo "\033[1mCleaning the mlx (aka minilibX) object and archive files\033[0m"
					@$(MAKE) clean -C $(MINILIB_DIR)

fclean:				clean
					@echo "\033[1;31m\033[1mDeleting the executable and archive files\033[0m" 
					$(RM) $(NAME)
					@echo ""
					@echo "\033[1;31m\033[1mCleaning the libft object and archive files\033[0m"
					$(MAKE) fclean -C $(LIBFT_DIR)

re:					fclean all

.PHONY:				all clean fclean re

#MINILIB
# ifeq ($(UNAME), Darwin)
# 	MINILIB_DIR = ./mlx_macOS
# 	MINILIB_ARCHIVE = $(MINILIB_DIR)/libmlx.a
# 	MINILIB_FLAGS = -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
# 	INCLUDES = -I./headers -Imlx
# else ifeq ($(UNAME), Linux)
# 	MINILIB_DIR = ./mlx
# 	MINILIB_ARCHIVE = $(MINILIB_DIR)/libmlx_Linux.a
# 	MINILIB_FLAGS = -Lmlx -lmlx -lm -L/usr/lib/X11 -lXext -lX11
# 	INCLUDES = -I./headers -I./usr/include -Imlx
# 	LINK_FLAGS = -ldl -lm -lpthread
# endif
