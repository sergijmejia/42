# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/09/17 18:36:40 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= libft.a
OBJ_DIR	= ./obj
INC_DIR	= ./includes
SRC_DIR	= ./srcs
OBJS	= $(OBJ_DIR)/ft_putchar.o \
	$(OBJ_DIR)/ft_putstr.o \
	$(OBJ_DIR)/ft_strcmp.o \
	$(OBJ_DIR)/ft_strlen.o \
	$(OBJ_DIR)/ft_swap.o

CFLAGS	= -Wall -Werror -Wextra -I$(INC_DIR)
CC	= gcc

all : $(TARGET)

$(TARGET) : $(OBJS)
	ar rcs $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

.PHONY : clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY : fclean
fclean:
	$(MAKE) clean
	rm -f $(TARGET)

.PHONY : re
re:
	$(MAKE) fclean
	$(MAKE)
