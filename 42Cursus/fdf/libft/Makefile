# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2025/02/18 11:33:02 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= ./src
SRC	= $(OBJ_DIR)/ft_isalpha.o		\
	  $(OBJ_DIR)/ft_isdigit.o		\
	  $(OBJ_DIR)/ft_isalnum.o		\
	  $(OBJ_DIR)/ft_isascii.o		\
	  $(OBJ_DIR)/ft_isprint.o		\
	  $(OBJ_DIR)/ft_strlen.o		\
	  $(OBJ_DIR)/ft_memset.o		\
	  $(OBJ_DIR)/ft_bzero.o			\
	  $(OBJ_DIR)/ft_memcpy.o		\
	  $(OBJ_DIR)/ft_memmove.o		\
	  $(OBJ_DIR)/ft_strlcpy.o		\
	  $(OBJ_DIR)/ft_strlcat.o		\
	  $(OBJ_DIR)/ft_toupper.o		\
	  $(OBJ_DIR)/ft_tolower.o		\
	  $(OBJ_DIR)/ft_strtoupper.o		\
	  $(OBJ_DIR)/ft_strchr.o		\
	  $(OBJ_DIR)/ft_strrchr.o		\
	  $(OBJ_DIR)/ft_strncmp.o		\
	  $(OBJ_DIR)/ft_memchr.o		\
	  $(OBJ_DIR)/ft_memcmp.o		\
	  $(OBJ_DIR)/ft_strnstr.o		\
	  $(OBJ_DIR)/ft_atoi.o			\
	  $(OBJ_DIR)/ft_calloc.o		\
	  $(OBJ_DIR)/ft_strdup.o		\
	  $(OBJ_DIR)/ft_substr.o		\
	  $(OBJ_DIR)/ft_strjoin.o		\
	  $(OBJ_DIR)/ft_strcontains.o		\
	  $(OBJ_DIR)/ft_strtrim.o		\
	  $(OBJ_DIR)/ft_countchar.o		\
	  $(OBJ_DIR)/ft_countwords.o		\
	  $(OBJ_DIR)/ft_split.o			\
	  $(OBJ_DIR)/ft_intlen.o		\
	  $(OBJ_DIR)/ft_abs.o			\
	  $(OBJ_DIR)/ft_itoa.o			\
	  $(OBJ_DIR)/ft_strmapi.o		\
	  $(OBJ_DIR)/ft_striteri.o		\
	  $(OBJ_DIR)/ft_putchar_fd.o		\
	  $(OBJ_DIR)/ft_putstr_fd.o		\
	  $(OBJ_DIR)/ft_putendl_fd.o		\
	  $(OBJ_DIR)/ft_putnbr_fd.o		\
	  $(OBJ_DIR)/ft_putchar.o		\
	  $(OBJ_DIR)/ft_putstr.o		\
	  $(OBJ_DIR)/ft_atol.o			\
	  $(OBJ_DIR)/ft_lstnew.o		\
	  $(OBJ_DIR)/ft_lstadd_front.o		\
	  $(OBJ_DIR)/ft_lstsize.o		\
	  $(OBJ_DIR)/ft_lstlast.o		\
	  $(OBJ_DIR)/ft_lstadd_back.o		\
	  $(OBJ_DIR)/ft_lstdelone.o		\
	  $(OBJ_DIR)/ft_lstclear.o		\
	  $(OBJ_DIR)/ft_lstiter.o		\
	  $(OBJ_DIR)/ft_lstmap.o		\
	  $(OBJ_DIR)/ft_lstpos.o		\
	  $(OBJ_DIR)/ft_lstsecondlast.o		\
	  $(OBJ_DIR)/get_next_line.o		\
	  $(OBJ_DIR)/ft_check_newline.o		\
	  $(OBJ_DIR)/ft_free_str.o		\
	  $(OBJ_DIR)/ft_printf.o		\
	  $(OBJ_DIR)/ft_cal_min_field.o		\
	  $(OBJ_DIR)/ft_cal_prec.o		\
	  $(OBJ_DIR)/ft_count_arg_len.o		\
	  $(OBJ_DIR)/ft_create_arg.o		\
	  $(OBJ_DIR)/ft_flag.o			\
	  $(OBJ_DIR)/ft_numlen.o		\
	  $(OBJ_DIR)/ft_character.o		\
	  $(OBJ_DIR)/ft_string.o		\
	  $(OBJ_DIR)/ft_hexa_pointer.o		\
	  $(OBJ_DIR)/ft_integer.o		\
	  $(OBJ_DIR)/ft_apply_min_field_int.o	\
	  $(OBJ_DIR)/ft_unsig_int.o		\
	  $(OBJ_DIR)/ft_hexa_num_lower.o	\
	  $(OBJ_DIR)/ft_hexa_num_upper.o	\
	  $(OBJ_DIR)/ft_create_character_arg.o	\

HEADER	= libft.h

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Werror -Wextra -I$(INC_DIR)
CC	= cc

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)
