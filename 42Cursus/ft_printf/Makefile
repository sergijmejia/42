# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/11/02 15:40:18 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
OBJ_DIR	= ./obj
INC_DIR	= ./inc
SRC_DIR	= ./src
LIB_DIR = ./lib
OBJS	= $(OBJ_DIR)/ft_printf.o        	\
          $(OBJ_DIR)/ft_cal_min_field.o 	\
	  $(OBJ_DIR)/ft_create_arg.o    	\
          $(OBJ_DIR)/ft_hexa_pointer.o 	  	\
          $(OBJ_DIR)/ft_cal_prec.o   	    	\
          $(OBJ_DIR)/ft_flag.o 		   	\
          $(OBJ_DIR)/ft_integer.o           	\
          $(OBJ_DIR)/ft_character.o         	\
          $(OBJ_DIR)/ft_hexa_num_lower.o    	\
          $(OBJ_DIR)/ft_numlen.o    		\
          $(OBJ_DIR)/ft_string.o 		\
          $(OBJ_DIR)/ft_count_arg_len.o    	\
          $(OBJ_DIR)/ft_hexa_num_upper.o 	\
          $(OBJ_DIR)/ft_unsig_int.o		\
	  $(OBJ_DIR)/ft_integer_2.o



CFLAGS	= -Wall -Werror -Wextra -I$(INC_DIR) -g
CC	= cc

LIBS    = -L$(LIB_DIR) -lft

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS) $(MAKEFILE_LIST)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)
