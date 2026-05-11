# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaguti <rafaguti>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/02 18:00:29 by rafaguti          #+#    #+#              #
#    Updated: 2026/05/02 18:00:35 by rafaguti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

NAME        := miniRT

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

INCLUDES    := -I include -I libft/include -I minilibx

SRC_DIR_M   := src_mandatory
SRC_DIR_B   := src_bonus
OBJ_DIR     := obj

LIBFT_DIR   := libft
MLX_DIR     := minilibx

LIBFT       := $(LIBFT_DIR)/libft.a
MLX         := $(MLX_DIR)/libmlx.a

# --- mandatory sources (42 subject: mandatory part) ------------------------- #

SRC_M       := main.c init.c cleanup.c hooks.c vec_utils.c vec_utils_ext.c \
		color_utils.c geometry.c geometry_utils.c parse.c parse_utils.c \
		parse_types.c parse_env.c parse_objs.c parse_read.c render.c \
		render_present_image.c trace.c trace_normals.c lighting.c bonus_stub.c

# --- bonus: extra sources, no stub/lighting_mandatory ----------------------- #

ifeq ($(BONUS),1)
CFLAGS      += -DBONUS
SRC_M       := main.c init.c cleanup.c hooks.c vec_utils.c vec_utils_ext.c \
		color_utils.c geometry.c geometry_utils.c parse_utils.c \
		parse_types.c parse_env.c parse_objs.c parse_read.c render.c \
		render_present_image.c
SRC_B       := parse_bonus.c parse_utils_bonus.c parse_elements_bonus.c \
		cone_bonus.c cone_utils_bonus.c trace_bonus.c trace_normals_bonus.c \
		cone_intersection_logic_bonus.c color_utils_bonus.c lighting_bonus.c
else
SRC_B       :=
endif

OBJS_M      := $(addprefix $(OBJ_DIR)/,$(SRC_M:.c=.o))
OBJS_B      := $(addprefix $(OBJ_DIR)/,$(SRC_B:.c=.o))
OBJS        := $(OBJS_M) $(OBJS_B)

GREEN       := \033[0;32m
CYAN        := \033[0;36m
YELLOW      := \033[0;33m
RED         := \033[0;31m
RESET       := \033[0m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX) | $(OBJ_DIR)
	@echo "$(CYAN)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) \
	-lXext -lX11 -lm -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR_M)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🛠  Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR_B)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🛠  Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(CYAN)📚 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "$(CYAN)🖼  Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)

clean:
	@echo "$(RED)🧹 Cleaning objects...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)🗑  Removing binary...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re: fclean all

bonus:
	@$(MAKE) BONUS=1 re

.PHONY: all clean fclean re bonus
