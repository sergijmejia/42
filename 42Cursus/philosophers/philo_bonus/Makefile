# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 18:26:02 by smejia-a          #+#    #+#              #
#    Updated: 2025/11/24 13:47:59 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= philo_bonus
OBJ_DIR	= ./obj
INC_DIR	= ./inc
SRC_DIR	= ./src

MAIN_PHILO = $(OBJ_DIR)/philo_bonus.o

OBJS	=	$(OBJ_DIR)/complete_data_bonus.o	\
			$(OBJ_DIR)/input_values_bonus.o		\
			$(OBJ_DIR)/monitor_bonus.o			\
			$(OBJ_DIR)/philo_eat_bonus.o		\
			$(OBJ_DIR)/philo_sleep_bonus.o		\
			$(OBJ_DIR)/philo_think_bonus.o		\
			$(OBJ_DIR)/print_philo_bonus.o		\
			$(OBJ_DIR)/routine_bonus.o			\
			$(OBJ_DIR)/utils_bonus.o

MAIN_PHILO_BONUS =

OBJS_BONUS	=

HEADER	= $(INC_DIR)/philo_bonus.h

ifndef BONUS
	OBJ = $(OBJS)
	MAIN = $(MAIN_PHILO)
else
	OBJ = $(OBJS) $(OBJS_BONUS)
	MAIN = $(MAIN_PHILO_BONUS)
endif

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -g
CC	= cc

.PHONY : all bonus clean fclean re

all : $(TARGET)

$(TARGET) : $(MAIN) $(OBJ) $(HEADER)
	$(CC) $(MAIN) $(OBJ) -o $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus:	
	@make BONUS=1

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)

re:
	$(MAKE) fclean
	$(MAKE)
