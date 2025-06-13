# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2025/06/08 13:49:13 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= minishell
TARGET_BONUS =
TARGET_TEST = tester
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
TEST_DIR = ./test
LIB_DIR = ./libft

MAIN_MINISHELL = $(OBJ_DIR)/main.o 

OBJS	= $(OBJ_DIR)/quote_divider.o		\
		  $(OBJ_DIR)/print_lst.o

MAIN_BONUS =

OBJS_BONUS =

MAIN_TEST = $(OBJ_DIR)/checker.o

OBJS_TEST =

HEADER	= $(INC_DIR)/minishell.h

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -g
CC	= cc
LIBS	= $(LIB_DIR)/libft.a

.PHONY : all bonus test clean fclean re

all : LIBFT $(TARGET)

LIBFT:
	$(MAKE) -C $(LIB_DIR)

$(TARGET) : $(MAIN_MINISHELL) $(OBJS) $(HEADER)
	$(CC) $(MAIN_MINISHELL) $(OBJS) $(LIBS) -o $(TARGET)

$(TARGET_BONUS) : $(MAIN_BONUS) $(OBJS) $(OBJS_BONUS) $(HEADER)
	$(CC) $(MAIN_BONUS) $(OBJS) $(OBJS_BONUS) $(LIBS) -o $(TARGET_BONUS)

$(TARGET_TEST) : $(MAIN_TEST) $(OBJS) $(OBJS_TEST) $(HEADER)
	$(CC) $(MAIN_TEST) $(OBJS) $(OBJS_TEST) $(LIBS) -o $(TARGET_TEST)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus: all $(TARGET_BONUS)

test: LIBFT $(TARGET_TEST)

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
