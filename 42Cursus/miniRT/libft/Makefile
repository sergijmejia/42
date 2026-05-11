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
SRC_BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

# Source Files
SRCS = $(SRC_DIR)/ft_bzero.c \
		$(SRC_DIR)/ft_isalnum.c \
		$(SRC_DIR)/ft_isalpha.c \
		$(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isdigit.c \
		$(SRC_DIR)/ft_isprint.c \
		$(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c \
		$(SRC_DIR)/ft_memset.c \
		$(SRC_DIR)/ft_strlcat.c \
		$(SRC_DIR)/ft_strlcpy.c \
		$(SRC_DIR)/ft_strlen.c \
		$(SRC_DIR)/ft_toupper.c \
		$(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_strchr.c \
		$(SRC_DIR)/ft_strrchr.c \
		$(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_memchr.c \
		$(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_strnstr.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_strdup.c \
		$(SRC_DIR)/ft_substr.c \
		$(SRC_DIR)/ft_strjoin.c \
		$(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_striteri.c \
		$(SRC_DIR)/ft_putchar_fd.c \
		$(SRC_DIR)/ft_putstr_fd.c \
		$(SRC_DIR)/ft_putendl_fd.c \
		$(SRC_DIR)/ft_putnbr_fd.c

# Source bonus files
BONUS_SRCS = $(SRC_BONUS_DIR)/ft_lstnew_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstadd_front_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstsize_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstlast_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstadd_back_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstdelone_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstclear_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstiter_bonus.c \
		$(SRC_BONUS_DIR)/ft_lstmap_bonus.c

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Object bonus files
BONUS_OBJS = $(patsubst $(SRC_BONUS_DIR)/%.c,$(OBJ_BONUS_DIR)/%.o,$(BONUS_SRCS))

# Header File
HEADER = $(INC_DIR)/libft.h
BONUS_HEADER = $(INC_DIR)/libft_bonus.h

# Targets rules
all: mandatory

mandatory:
	@if [ -f .bonus_compiled ]; then \
		rm -f $(NAME); \
		$(MAKE) -C . make_mandatory; \
	fi
	@if [ ! -f $(NAME) ]; then \
		$(MAKE) -C . make_mandatory; \
	else \
		if [ -n "$$(find $(SRC_DIR) -newer $(NAME))" ]; then \
			$(MAKE) -C . make_mandatory; \
		else \
			echo "make: Nothing to be done for 'all'."; \
		fi; \
	fi

make_mandatory: check_mandatory build_mandatory

check_mandatory:
	@if [ ! -f .mandatory_compiled ] || [ -n "$(shell $(MAKE) -q build_mandatory 2>/dev/null || echo 1)" ]; then \
		echo "$(BOLD)$(WHITE)> $(NAME):$(RESET)"; \
	else \
		echo "make: Nothing to be done for 'all'."; \
	fi

build_mandatory: $(OBJS)
	@ar rcs $(NAME) $?
	@echo "$(BOLD)$(WHITE)>> Library build successfully! 🎉$(RESET)"
	@touch .mandatory_compiled
	@rm -f .bonus_compiled

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@echo "$(CYAN)>> Compiling $<... $(BOLD)$(GREEN)[ OK ]$(RESET)"
	@$(CC) $(ALL_CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(BONUS_HEADER) | $(OBJ_BONUS_DIR)
	@echo "$(MAGENTA)>> Compiling $<... $(BOLD)$(GREEN)[ OK ]$(RESET)"
	@$(CC) $(ALL_CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_BONUS_DIR):
	@mkdir -p $@

# Bonus
bonus:
	@if [ -f .mandatory_compiled ] || [ ! -f $(NAME) ]; then \
		$(MAKE) -C . make_bonus; \
	else \
		if [ -n "$$(find $(SRC_BONUS_DIR) -newer $(NAME))" ]; then \
			$(MAKE) -C . make_bonus; \
		else \
			echo "make: Nothing to be done for 'all'."; \
		fi; \
	fi

make_bonus: check_bonus build_bonus

check_bonus:
	@if [ ! -f .bonus_compiled ] || [ -n "$(shell $(MAKE) -q build_bonus 2>/dev/null || echo 1)" ]; then \
		echo "$(BOLD)$(WHITE)> $(NAME):$(RESET)"; \
	else \
		echo "make: Nothing to be done for 'bonus'."; \
	fi

# Creating the static library with bonus
build_bonus: $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $?
	@echo "$(BOLD)$(WHITE)>> Library with bonus build successfully! ✨$(RESET)"
	@touch .bonus_compiled
	@rm -f .mandatory_compiled

# Clean Object Files
clean:
	@echo "$(BOLD)$(WHITE)> $(NAME):$(RESET)"
	@if [ ! -d "$(OBJ_DIR)" ] && [ ! -d "$(OBJ_BONUS_DIR)" ]; then \
		echo "$(BOLD)$(YELLOW)>> No object files to clean$(RESET)"; \
	else \
		echo -n "$(BOLD)$(YELLOW)>> Cleaning object files...$(RESET)"; \
		rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) .mandatory_compiled .bonus_compiled; \
		echo "$(BOLD)$(GREEN) [ OK ]$(RESET)"; \
	fi

# Full Clean
fclean: clean
	@if [ -f "$(NAME)" ] || [ -f ".bonus" ]; then \
		echo -n "$(BOLD)$(RED)>> Removing library...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(BOLD)$(GREEN) [ OK ]$(RESET)"; \
	else \
		echo "$(BOLD)$(RED)>> Library does not exist or already removed$(RESET)"; \
	fi

# Rebuild the Project
re: fclean all

# Phony Targets
.PHONY: all clean fclean re mandatory check_mandatory make_mandatory build_mandatory bonus check_bonus make_bonus build_bonus
