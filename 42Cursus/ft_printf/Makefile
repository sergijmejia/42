# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/11/06 18:49:24 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
OBJS	= $(OBJ_DIR)/ft_printf.o        	\
          $(OBJ_DIR)/ft_cal_min_field.o 	\
	  $(OBJ_DIR)/ft_create_arg.o    	\
          $(OBJ_DIR)/ft_hexa_pointer.o 	  	\
          $(OBJ_DIR)/ft_cal_prec.o   	    	\
          $(OBJ_DIR)/ft_flag.o 		   	\
          $(OBJ_DIR)/ft_integer.o           	\
	  $(OBJ_DIR)/ft_integer_2.o		\
          $(OBJ_DIR)/ft_character.o         	\
          $(OBJ_DIR)/ft_hexa_num_lower.o    	\
          $(OBJ_DIR)/ft_numlen.o    		\
          $(OBJ_DIR)/ft_string.o 		\
          $(OBJ_DIR)/ft_count_arg_len.o    	\
          $(OBJ_DIR)/ft_hexa_num_upper.o 	\
          $(OBJ_DIR)/ft_unsig_int.o		\
          $(OBJ_DIR)/ft_strcontains.o		\
          $(OBJ_DIR)/ft_isdigit.o		\
          $(OBJ_DIR)/ft_strlen.o		\
          $(OBJ_DIR)/ft_memset.o		\
          $(OBJ_DIR)/ft_strlcpy.o		\
          $(OBJ_DIR)/ft_memcpy.o		\
          $(OBJ_DIR)/ft_strdup.o		\
          $(OBJ_DIR)/ft_strtoupper.o		\
          $(OBJ_DIR)/ft_toupper.o		\
          $(OBJ_DIR)/ft_putchar.o		\
          $(OBJ_DIR)/ft_putstr.o		\
          $(OBJ_DIR)/ft_itoa.o			\
          $(OBJ_DIR)/ft_calloc.o		\
          $(OBJ_DIR)/ft_intlen.o		\
          $(OBJ_DIR)/ft_abs.o			\
          $(OBJ_DIR)/ft_bzero.o			\
	  $(OBJ_DIR)/ft_strrchr.o		\
	  $(OBJ_DIR)/ft_memcmp.o		\
	  $(OBJ_DIR)/ft_create_character_arg.o

OBJS_BONUS =

HEADER	= ft_printf.h

CFLAGS	= -Wall -Werror -Wextra -I$(INC_DIR)
CC	= cc

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

bonus: $(OBJS) $(OBJS_BONUS) $(HEADER)
	ar rcs $(NAME) $^
	@touch $@


clean:
	rm -rf $(OBJ_DIR) $(OBJS_BONUS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)
	@${RM} bonus

re:
	$(MAKE) fclean
	$(MAKE)
