# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/10/02 02:00:18 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= ft_atoi
OBJ_DIR	= ./obj
INC_DIR	= .
SRC_DIR	= .
OBJS	= $(OBJ_DIR)/ft_isalpha.o \
	  $(OBJ_DIR)/ft_isdigit.o \
	  $(OBJ_DIR)/ft_isalnum.o \
	  $(OBJ_DIR)/ft_isascii.o \
	  $(OBJ_DIR)/ft_isprint.o \
	  $(OBJ_DIR)/ft_strlen.o  \
	  $(OBJ_DIR)/ft_memset.o  \
	  $(OBJ_DIR)/ft_bzero.o   \
	  $(OBJ_DIR)/ft_memcpy.o  \
	  $(OBJ_DIR)/ft_memmove.o \
	  $(OBJ_DIR)/ft_strlcpy.o \
	  $(OBJ_DIR)/ft_strlcat.o \
	  $(OBJ_DIR)/ft_toupper.o \
	  $(OBJ_DIR)/ft_tolower.o \
	  $(OBJ_DIR)/ft_strchr.o  \
	  $(OBJ_DIR)/ft_strrchr.o \
	  $(OBJ_DIR)/ft_strncmp.o \
	  $(OBJ_DIR)/ft_memchr.o  \
	  $(OBJ_DIR)/ft_memcmp.o  \
	  $(OBJ_DIR)/ft_strnstr.o \
	  $(OBJ_DIR)/ft_atoi.o

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
