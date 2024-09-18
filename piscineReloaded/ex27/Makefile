# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 12:40:47 by smejia-a          #+#    #+#              #
#    Updated: 2024/09/18 14:47:32 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= ft_display_file
OBJ_DIR	= ./obj
SRC_DIR	= ./srcs
OBJS	= $(OBJ_DIR)/ft_display.o

CFLAGS	= -Wall -Werror -Wextra 
CC	= cc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY : fclean
fclean:
	$(MAKE) clean
	rm -f $(TARGET)


