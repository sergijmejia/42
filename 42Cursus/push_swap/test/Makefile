# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/12/21 13:53:43 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= push_swap
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= .
LIB_DIR = ..
OBJS	= $(OBJ_DIR)/test.o

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
