# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/10/05 02:44:37 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= ft_itoa
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= .
OBJS	= $(OBJ_DIR)/ft_isalpha.o     \
	  $(OBJ_DIR)/ft_isdigit.o     \
	  $(OBJ_DIR)/ft_isalnum.o     \
	  $(OBJ_DIR)/ft_isascii.o     \
	  $(OBJ_DIR)/ft_isprint.o     \
	  $(OBJ_DIR)/ft_strlen.o      \
	  $(OBJ_DIR)/ft_memset.o      \
	  $(OBJ_DIR)/ft_bzero.o       \
	  $(OBJ_DIR)/ft_memcpy.o      \
	  $(OBJ_DIR)/ft_memmove.o     \
	  $(OBJ_DIR)/ft_strlcpy.o     \
	  $(OBJ_DIR)/ft_strlcat.o     \
	  $(OBJ_DIR)/ft_toupper.o     \
	  $(OBJ_DIR)/ft_tolower.o     \
	  $(OBJ_DIR)/ft_strchr.o      \
	  $(OBJ_DIR)/ft_strrchr.o     \
	  $(OBJ_DIR)/ft_strncmp.o     \
	  $(OBJ_DIR)/ft_memchr.o      \
	  $(OBJ_DIR)/ft_memcmp.o      \
	  $(OBJ_DIR)/ft_strnstr.o     \
	  $(OBJ_DIR)/ft_atoi.o        \
	  $(OBJ_DIR)/ft_calloc.o      \
	  $(OBJ_DIR)/ft_strdup.o      \
	  $(OBJ_DIR)/ft_substr.o      \
	  $(OBJ_DIR)/ft_strjoin.o     \
	  $(OBJ_DIR)/ft_strcontains.o \
	  $(OBJ_DIR)/ft_strtrim.o     \
	  $(OBJ_DIR)/ft_countchar.o   \
	  $(OBJ_DIR)/ft_split.o       \
	  $(OBJ_DIR)/ft_intlen.o      \
	  $(OBJ_DIR)/ft_abs.o         \
	  $(OBJ_DIR)/ft_itoa.o        \
	  $(OBJ_DIR)/ft_strmapi.o     \
	  $(OBJ_DIR)/ft_striteri.o    \
	  $(OBJ_DIR)/ft_putchar_fd.o  \
	  $(OBJ_DIR)/ft_putstr_fd.o   \
	  $(OBJ_DIR)/ft_putendl_fd.o  \
	  $(OBJ_DIR)/ft_putnbr_fd.o

CFLAGS	= -Wall -Werror -Wextra -I$(INC_DIR)
CC	= cc

all : $(TARGET)

$(TARGET) : $(OBJS) $(MAKEFILE_LIST)
	$(CC) $(OBJS) -o $(TARGET)

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
