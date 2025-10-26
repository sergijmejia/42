# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaguti <rafaguti>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/18 00:59:49 by rafaguti          #+#    #+#              #
#    Updated: 2025/10/18 01:10:52 by rafaguti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors and Formatting
RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

# Project Configuration
NAME = libft.a
CC = cc
WARNING_FLAGS = -Wall -Werror -Wextra
INCLUDE_FLAGS = -I$(INC_DIR)
ALL_CFLAGS = $(WARNING_FLAGS) $(INCLUDE_FLAGS)
MAKE = make --no-print-directory

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source Files
SRCS = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset ft_bzero \
	ft_memcpy ft_memmove ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strtoupper ft_strchr \
	ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi ft_calloc ft_strdup ft_substr \
	ft_strjoin ft_strcontains ft_strtrim ft_countchar ft_countwords ft_split ft_intlen ft_abs \
	ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
	ft_putchar ft_putstr ft_atol ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
	ft_lstdelone ft_lstclear ft_lstiter ft_lstmap ft_lstpos ft_lstsecondlast get_next_line \
	ft_check_newline ft_free_str ft_printf ft_cal_min_field ft_cal_prec ft_count_arg_len \
	ft_create_arg ft_flag ft_numlen ft_character ft_string ft_hexa_pointer ft_integer \
	ft_apply_min_field_int ft_unsig_int ft_hexa_num_lower ft_hexa_num_upper ft_create_character_arg \
	ft_lstadd_pos ft_lstdel_pos ft_lstdel_last ft_getenv

OBJS = $(patsubst %,$(OBJ_DIR)/%.o,$(SRCS))

# Header File
HEADER = $(INC_DIR)/libft.h

# Targets rules
all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@ar rcs $(NAME) $?
	@echo "$(BOLD)$(WHITE)>> Library build successfully! 🎉$(RESET)"

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@echo "$(CYAN)>> Compiling $<... $(BOLD)$(GREEN)[ OK ]$(RESET)"
	@$(CC) $(ALL_CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

# Clean Object Files
clean:
	@echo -n "$(BOLD)$(WHITE)>> Cleaning object files$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BOLD)$(GREEN)[ OK ]$(RESET)"

# Full Clean
fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo -n "$(BOLD)$(RED)>> Removing library...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(BOLD)$(GREEN) [ OK ]$(RESET)"; \
	else \
		echo "$(BOLD)$(RED)>> Library does not exist or already removed$(RESET)"; \
	fi

# Rebuild the Project
re: fclean all

# Phony Targets
.PHONY: all clean fclean re
