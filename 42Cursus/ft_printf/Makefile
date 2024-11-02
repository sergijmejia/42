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

TARGET	= ft_printf
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= .
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
          $(OBJ_DIR)/ft_unsig_int.o


CFLAGS	= -Wall -Werror -Wextra -I$(INC_DIR) -g
CC	= cc

LIB_DIR = .
LIBS    = -L$(LIB_DIR) -lft

.PHONY : all clean fclean re

all : $(TARGET)

$(TARGET) : $(OBJS) $(MAKEFILE_LIST)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)

re:
	$(MAKE) fclean
	$(MAKE)
