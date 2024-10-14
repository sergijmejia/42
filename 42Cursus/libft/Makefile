# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2024/10/14 20:09:21 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= libft.a
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
	  $(OBJ_DIR)/ft_strtoupper.o  \
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
	  $(OBJ_DIR)/ft_countwords.o  \
	  $(OBJ_DIR)/ft_split.o       \
	  $(OBJ_DIR)/ft_intlen.o      \
	  $(OBJ_DIR)/ft_abs.o         \
	  $(OBJ_DIR)/ft_itoa.o        \
	  $(OBJ_DIR)/ft_strmapi.o     \
	  $(OBJ_DIR)/ft_striteri.o    \
	  $(OBJ_DIR)/ft_putchar_fd.o  \
	  $(OBJ_DIR)/ft_putstr_fd.o   \
	  $(OBJ_DIR)/ft_putendl_fd.o  \
	  $(OBJ_DIR)/ft_putnbr_fd.o   \
	  $(OBJ_DIR)/ft_lstnew.o      \
	  $(OBJ_DIR)/ft_lstadd_front.o\
	  $(OBJ_DIR)/ft_lstadd_back.o \
	  $(OBJ_DIR)/ft_lstdelone.o   \
	  $(OBJ_DIR)/ft_lstclear.o    \
	  $(OBJ_DIR)/ft_lstsize.o     \
	  $(OBJ_DIR)/ft_lstiter.o     \
	  $(OBJ_DIR)/ft_lstmap.o      \
	  $(OBJ_DIR)/ft_lstlast.o

OBJS_BONUS = $(OBJ_DIR)/ft_lstnew.o       \
	     $(OBJ_DIR)/ft_lstadd_front.o \
	     $(OBJ_DIR)/ft_lstsize.o      \
	     $(OBJ_DIR)/ft_lstlast.o      \
	     $(OBJ_DIR)/ft_lstadd_back.o  \
	     $(OBJ_DIR)/ft_lstdelone.o    \
	     $(OBJ_DIR)/ft_lstclear.o     \
	     $(OBJ_DIR)/ft_lstiter.o      \
	     $(OBJ_DIR)/ft_lstmap.o


CFLAGS	= -Wall -Werror -Wextra -I$(INC_DIR)
CC	= gcc

.PHONY : all bonus clean fcclean re

all : $(TARGET)

$(TARGET) : $(OBJS) $(MAKEFILE_LIST)
	ar rcs $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c -MD $(CFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

bonus: $(OBJS) $(OBJS_BONUS) $(MAKEFILE_LIST)
	$(CC) $(OBJS) $(OBJS_BONUS) -o $(TARGET)

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)

re:
	$(MAKE) fclean
	$(MAKE)
