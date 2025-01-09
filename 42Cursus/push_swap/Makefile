# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2025/01/09 14:01:51 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= push_swap
TARGET_BONUS = checker
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
LIB_DIR = ./libft

MAIN_PUSHSWAP = $(OBJ_DIR)/push_swap.o

OBJS	= $(OBJ_DIR)/push_swap_rules.o		\
	  $(OBJ_DIR)/push_swap_rules_2.o	\
	  $(OBJ_DIR)/push_swap_utils.o		\
	  $(OBJ_DIR)/push_swap_utils_2.o	\
	  $(OBJ_DIR)/push_swap_errors.o		\
	  $(OBJ_DIR)/push_swap_organize.o	\
	  $(OBJ_DIR)/push_swap_count_moves.o	\
	  $(OBJ_DIR)/push_swap_do_moves.o	\
	  $(OBJ_DIR)/push_swap_setters.o	\
	  $(OBJ_DIR)/push_swap_min_move.o

MAIN_CHECKER = $(OBJ_DIR)/checker_bonus.o

OBJS_BONUS = $(OBJ_DIR)/checker_utils_bonus.o

HEADER	= $(INC_DIR)/push_swap.h

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -g
CC	= cc
LIBS	= $(LIB_DIR)/libft.a

.PHONY : all bonus clean fclean re

all : LIBFT $(TARGET)

LIBFT:
	$(MAKE) -C $(LIB_DIR)

$(TARGET) : $(MAIN_PUSHSWAP) $(OBJS) $(HEADER)
	$(CC) $(MAIN_PUSHSWAP) $(OBJS) $(LIBS) -o $(TARGET)

$(TARGET_BONUS) : $(MAIN_CHECKER) $(OBJS) $(OBJS_BONUS) $(HEADER)
	$(CC) $(MAIN_CHECKER) $(OBJS) $(OBJS_BONUS) $(LIBS) -o $(TARGET_BONUS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus: all $(TARGET_BONUS)

clean:
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)
	rm -f $(TARGET_BONUS)

re:
	$(MAKE) fclean
	$(MAKE)
