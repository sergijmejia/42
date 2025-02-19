# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2025/02/19 10:59:49 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= fdf
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
LIB_DIR = ./libft
MLX_DIR = ./MLX42/build

MAIN_FDF = $(OBJ_DIR)/fdf.o

OBJS	= 

HEADER	= $(INC_DIR)/fdf.h

CFLAGS	= -Wall -Wextra -Werror -I./MLX42/include -I./libft -I$(INC_DIR) -g
LDFLAGS = -lglfw -ldl -lpthread -lm
CC	= cc
LIBS	= $(LIB_DIR)/libft.a		\
	  $(MLX_DIR)/libmlx42.a

.PHONY : all bonus clean fclean re

all : LIBFT $(TARGET)

LIBFT:
	@$(MAKE) -C $(LIB_DIR)

$(TARGET) : $(MAIN_FDF) $(OBJS) $(HEADER)
	$(CC) $(MAIN_FDF) $(OBJS) $(LIBS) $(LDFLAGS) -o $(TARGET)

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
