# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/11/14 16:45:01 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= test_2
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
SRC	= $(OBJ_DIR)/get_next_line_bonus.o		\
	  $(OBJ_DIR)/get_next_line_utils_bonus.o	\
	  $(OBJ_DIR)/test_2.o

SRC_BONUS =

HEADER	= $(INC_DIR)/get_next_line_bonus.h

ifndef BONUS
	OBJ = $(SRC:.c=.o)
else
	OBJ = $(SRC_BONUS:.c=.o) $(SRC:.c=.o)
endif
OBJ_BONUS = $(SRC_BONUS:.c=.o)

CFLAGS	= -Wall -Werror -Wextra -g -D BUFFER_SIZE=42 -I $(INC_DIR)
CC	= cc

.PHONY : all bonus clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus: 
	@make BONUS=1 --no-print-directory

clean:
	rm -rf $(OBJ_DIR) $(OBJS_BONUS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)
