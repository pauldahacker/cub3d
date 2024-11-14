# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 13:58:35 by pde-masc          #+#    #+#              #
#    Updated: 2024/09/19 15:08:23 by pde-masc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BROWN =	\033[38;2;184;143;29m
ORANGE = \033[38;5;209m
BLUE = \033[0;94m
DEF_COLOR = \033[0;39m
GREEN =	\033[0;92m

CC			= gcc
FLAGS		= -c -Wall -Wextra -Werror
LIB			= ar rcs
RM			= /bin/rm -f

NAME		= libft.a
HEADER		= libft.h

SRC			= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			  ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJ			= $(SRC:.c=.o)

BONUS_SRC	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			  ft_lstmap.c

BONUS_OBJ	= $(BONUS_SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ) $(HEADER)
		@$(LIB) $(NAME) $(OBJ)
		@echo "$(GREEN)libft compiled succesfully!$(DEF_COLOR)"

bonus:		$(OBJ) $(BONUS_OBJ) $(HEADER)
		@$(LIB) $(NAME) $(OBJ) $(BONUS_OBJ)
		@echo "$(GREEN)libft compiled succesfully!$(DEF_COLOR)"

%.o:		%.c $(HEADER) Makefile
		@echo "$(BROWN)Compiling   ${BLUE}→   $(ORANGE)$< $(DEF_COLOR)"
		@$(CC) $(FLAGS) -c -o $@ $<

clean:
		@$(RM) $(OBJ)
		@$(RM) $(BONUS_OBJ)
		@echo "$(BROWN)libft: $(GREEN)removed objects!$(DEF_COLOR)"

fclean:		clean
		@$(RM) $(NAME)
		@echo "$(BROWN)libft: $(GREEN)removed binaries!$(DEF_COLOR)"

re:			fclean all

rebonus:	fclean bonus

.PHONY:		clean fclean all re
