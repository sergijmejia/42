# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 12:47:48 by smejia-a          #+#    #+#              #
#    Updated: 2025/02/07 19:58:08 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= pipex
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
LIB_DIR = ./libft

MAIN_PIPEX = $(OBJ_DIR)/pipex.o

OBJS	= $(OBJ_DIR)/pipex_utils.o		\
	  $(OBJ_DIR)/pipex_child_parent.o	\
	  $(OBJ_DIR)/pipex_error.o		\
	  $(OBJ_DIR)/pipex_command_error.o	\
	  $(OBJ_DIR)/pipex_file_error.o

MAIN_PIPEX_BONUS = $(OBJ_DIR)/pipex_bonus.o

OBJS_BONUS	= $(OBJ_DIR)/pipex_parent_bonus.o	\
		  $(OBJ_DIR)/pipex_child_bonus.o

HEADER	= $(INC_DIR)/pipex.h

ifndef BONUS
	OBJ = $(OBJS)
	MAIN = $(MAIN_PIPEX)
else
	OBJ = $(OBJS) $(OBJS_BONUS)
	MAIN = $(MAIN_PIPEX_BONUS)
endif

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -g
CC	= cc
LIBS	= $(LIB_DIR)/libft.a

.PHONY : all bonus clean fclean re

all : LIBFT $(TARGET)

LIBFT:
	$(MAKE) -C $(LIB_DIR)

$(TARGET) : $(MAIN) $(OBJ) $(HEADER)
	$(CC) $(MAIN) $(OBJ) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus:	
	@make BONUS=1

clean:
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)

re:
	$(MAKE) fclean
	$(MAKE)
