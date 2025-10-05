# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2025/10/02 11:49:49 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= minishell
TARGET_BONUS =
OBJ_DIR	= ./obj
INC_DIR	= ./inc
SRC_DIR	= ./src
TEST_DIR = ./test
LIB_DIR = ./lib

SRC_LEX = $(SRC_DIR)/src_lexer
SRC_TR = $(SRC_DIR)/src_transition
SRC_PAR = $(SRC_DIR)/src_parser
SRC_CF = $(SRC_DIR)/src_clean_functions

MAIN =

SRCS = $(wildcard $(SRC_DIR)/*.c)	\
       $(wildcard $(SRC_LEX)/*.c)	\
       $(wildcard $(SRC_TR)/*.c)	\
       $(wildcard $(SRC_CF)/*.c)	\
	   $(wildcard $(SRC_PAR)/*.c)

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

MAIN_BONUS =

SRCS_BONUS =

OBJS_BONUS =

HEADER	= $(INC_DIR)/minishell.h

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -g
CC	= cc
LIBS	= $(LIB_DIR)/libft/libft.a -lreadline

.PHONY : all bonus test clean fclean re

all : LIBFT $(TARGET)

LIBFT:
	$(MAKE) -C $(LIB_DIR)/libft

$(TARGET) : $(MAIN) $(OBJS) $(HEADER)
	$(CC) $(MAIN) $(OBJS) $(LIBS) -o $(TARGET)

$(TARGET_BONUS) : $(MAIN_BONUS) $(OBJS) $(OBJS_BONUS) $(HEADER)
	$(CC) $(MAIN_BONUS) $(OBJS) $(OBJS_BONUS) $(LIBS) -o $(TARGET_BONUS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(SRC_LEX)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(SRC_TR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(SRC_PAR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(SRC_CF)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus: all $(TARGET_BONUS)

test: LIBFT $(TARGET_TEST)

clean:
	$(MAKE) fclean -C $(LIB_DIR)/libft
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)
	rm -f $(TARGET_BONUS)

re:
	$(MAKE) fclean
	$(MAKE)
