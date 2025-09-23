# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 18:16:51 by smejia-a          #+#    #+#              #
#    Updated: 2025/09/23 16:26:30 by smejia-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET	= minishell
TARGET_BONUS =
TARGET_TEST = tester
OBJ_DIR	= ./obj
INC_DIR	= ./inc
SRC_DIR	= ./src
TEST_DIR = ./test
LIB_DIR = ./lib

MAIN_MINISHELL = $(OBJ_DIR)/main.o 

OBJS	= $(OBJ_DIR)/check_parentheses_balance.o	\
		  $(OBJ_DIR)/check_quote_balance.o			\
		  $(OBJ_DIR)/lexer.o 						\
		  $(OBJ_DIR)/parentheses_divider.o			\
		  $(OBJ_DIR)/assignment_divider.o			\
		  $(OBJ_DIR)/space_divider.o				\
		  $(OBJ_DIR)/special_char_divider.o			\
		  $(OBJ_DIR)/special_char_divider_2.o		\
		  $(OBJ_DIR)/find_redirection.o				\
		  $(OBJ_DIR)/find_command_option.o			\
		  $(OBJ_DIR)/find_wildcard.o				\
		  $(OBJ_DIR)/variable_expansion.o			\
		  $(OBJ_DIR)/delete_quotes.o				\
		  $(OBJ_DIR)/assignment_selection.o			\
		  $(OBJ_DIR)/transition_lex_par.o			\
		  $(OBJ_DIR)/command_union.o				\
		  $(OBJ_DIR)/errors.o						\
		  $(OBJ_DIR)/print_lst.o					\
		  $(OBJ_DIR)/print_lst_tr.o					\
		  $(OBJ_DIR)/ft_lstadd_pos.o				\
		  $(OBJ_DIR)/ft_lstdel_pos.o				\
		  $(OBJ_DIR)/ft_lstdel_last.o

MAIN_BONUS =

OBJS_BONUS =

MAIN_TEST = $(OBJ_DIR)/checker.o

OBJS_TEST =

HEADER	= $(INC_DIR)/minishell.h

CFLAGS	= -Wall -Wextra -Werror -I$(INC_DIR) -g
CC	= cc
LIBS	= $(LIB_DIR)/libft/libft.a -lreadline

.PHONY : all bonus test clean fclean re

all : LIBFT $(TARGET)

LIBFT:
	$(MAKE) -C $(LIB_DIR)/libft

$(TARGET) : $(MAIN_MINISHELL) $(OBJS) $(HEADER)
	$(CC) $(MAIN_MINISHELL) $(OBJS) $(LIBS) -o $(TARGET)

$(TARGET_BONUS) : $(MAIN_BONUS) $(OBJS) $(OBJS_BONUS) $(HEADER)
	$(CC) $(MAIN_BONUS) $(OBJS) $(OBJS_BONUS) $(LIBS) -o $(TARGET_BONUS)

$(TARGET_TEST) : $(MAIN_TEST) $(OBJS) $(OBJS_TEST) $(HEADER)
	$(CC) $(MAIN_TEST) $(OBJS) $(OBJS_TEST) $(LIBS) -o $(TARGET_TEST)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) $(MAKEFILE_LIST)
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

bonus: all $(TARGET_BONUS)

test: LIBFT $(TARGET_TEST)

clean:
	$(MAKE) fclean -C $(LIB_DIR)/libft
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(TARGET)
	rm -f $(TARGET_BONUS)

re:
	$(MAKE) fclean
	$(MAKE)
