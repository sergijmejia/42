# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/07 18:26:02 by smejia-a          #+#    #+#              #
#    Updated: 2025/11/06 10:05:52 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= philo
OBJ_DIR	= ./obj
INC_DIR	= ./inc
SRC_DIR	= ./src

MAIN_PHILO = $(OBJ_DIR)/philo.o

OBJS	=	$(OBJ_DIR)/alive.o			\
			$(OBJ_DIR)/complete_data.o	\
			$(OBJ_DIR)/input_values.o	\
			$(OBJ_DIR)/monitor.o		\
			$(OBJ_DIR)/philo_eat.o		\
			$(OBJ_DIR)/philo_sleep.o	\
			$(OBJ_DIR)/philo_think.o	\
			$(OBJ_DIR)/print_philo.o	\
			$(OBJ_DIR)/routine.o		\
			$(OBJ_DIR)/utils.o

MAIN_PHILO_BONUS = 

OBJS_BONUS	=

HEADER	= $(INC_DIR)/philo.h

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
