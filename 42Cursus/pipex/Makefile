# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 12:47:48 by smejia-a          #+#    #+#              #
#    Updated: 2025/01/29 15:41:16 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= pipex
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
LIB_DIR = ./libft

OBJS	= $(OBJ_DIR)/pipex.o#		\
	  #$(OBJ_DIR)/pipex_utils.o

HEADER	= $(INC_DIR)/pipex.h

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -g #-fsanitize=address
CC	= cc
LIBS	= $(LIB_DIR)/libft.a

.PHONY : all clean fclean re

all : LIBFT $(TARGET)

LIBFT:
	$(MAKE) -C $(LIB_DIR)

$(TARGET) : $(OBJS) $(HEADER)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(MAKE) fclean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)

re:
	$(MAKE) fclean
	$(MAKE)
