# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2025/01/05 14:41:19 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= push_swap
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
LIB_DIR = ..
OBJS	= $(OBJ_DIR)/push_swap.o		\
	  $(OBJ_DIR)/push_swap_rules.o		\
	  $(OBJ_DIR)/push_swap_rules_2.o	\
	  $(OBJ_DIR)/push_swap_utils.o		\
	  $(OBJ_DIR)/push_swap_utils_2.o	\
	  $(OBJ_DIR)/push_swap_utils_3.o	\
	  $(OBJ_DIR)/push_swap_errors.o		\
	  $(OBJ_DIR)/push_swap_organize.o	\
	  $(OBJ_DIR)/push_swap_count_moves.o	\
	  $(OBJ_DIR)/push_swap_do_moves.o	\
	  $(OBJ_DIR)/push_swap_setters.o	\
	  $(OBJ_DIR)/push_swap_min_move.o

HEADER	= $(INC_DIR)/push_swap.h

CFLAGS	= -I$(INC_DIR) -g
CC	= cc
LIBS	= -L$(LIB_DIR) -lft

.PHONY : all clean fclean re

all : $(TARGET)

$(TARGET) : $(OBJS) $(HEADER)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)

re:
	$(MAKE) fclean
	$(MAKE)
