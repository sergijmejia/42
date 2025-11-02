# Colors and Formatting
RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
CYAN = \033[36m
WHITE = \033[37m

# Project Configuration
NAME = minishell
CC = cc
WARNING_FLAGS = -g -Wall -Wextra -Werror
MAKE = make --no-print-directory

OBJ_DIR = obj
LIBFT_DIR = lib/libft
SRC_EXEC_DIR = src_exec
SRC_PARSE_DIR = src_parse

# --------------------------
# PART 1: PARSER
# --------------------------
PARSER_INCLUDE_FLAGS = -Iinclude -Iinclude/parse -Ilib/libft/include
PARSER_CFLAGS = $(WARNING_FLAGS) $(PARSER_INCLUDE_FLAGS)

PARSER_SRCS = src_parse/src_clean_functions/clean_functions.c \
              src_parse/src_clean_functions/clean_utils.c   \
              src_parse/src_clean_functions/error_functions.c\
              src_parse/src_general/process_input.c \
              src_parse/src_general/check_env.c \
              src_parse/src_general/check_parentheses_balance.c \
              src_parse/src_general/check_quote_balance.c \
              src_parse/src_general/create_var_table.c  \
              src_parse/src_general/dup_env.c   \
              src_parse/src_general/minishell_utils.c   \
              src_parse/src_general/minishell_utils_2.c \
              src_parse/src_lexer/assignment_divider.c      \
              src_parse/src_lexer/assignment_divider_2.c    \
              src_parse/src_lexer/assignment_divider_3.c    \
              src_parse/src_lexer/assignment_divider_4.c    \
              src_parse/src_lexer/assignment_selection.c \
              src_parse/src_lexer/delete_quotes.c \
              src_parse/src_lexer/find_redirection.c \
              src_parse/src_lexer/find_var.c \
              src_parse/src_lexer/find_wildcard.c \
              src_parse/src_lexer/lexer.c \
              src_parse/src_lexer/parentheses_divider.c \
              src_parse/src_lexer/parentheses_divider_2.c \
              src_parse/src_lexer/space_divider.c \
              src_parse/src_lexer/space_divider_2.c \
              src_parse/src_lexer/special_char_divider.c \
              src_parse/src_lexer/special_char_divider_2.c \
              src_parse/src_lexer/special_char_divider_3.c \
			  src_parse/src_lexer/special_char_divider_4.c \
              src_parse/src_lexer/variable_expansion.c \
              src_parse/src_lexer/variable_expansion_2.c \
              src_parse/src_transition/command_union.c  \
              src_parse/src_transition/command_union_2.c  \
              src_parse/src_transition/heredoc.c \
              src_parse/src_transition/heredoc_2.c \
              src_parse/src_transition/syntax_and_heredoc.c \
              src_parse/src_transition/syntax_and_heredoc_2.c \
              src_parse/src_transition/syntax_and_heredoc_3.c \
              src_parse/src_transition/transition.c \
              src_parse/src_transition/transition_lex_par.c \
              src_parse/src_transition/transition_lex_par_2.c \
              src_parse/src_transition/transition_lex_par_3.c \
              src_parse/src_transition/transition_lex_par_4.c \
              src_parse/src_transition/transition_lex_par_5.c \
              src_parse/src_transition/utils_transition.c \
              src_parse/src_parser/create_ast.c \
              src_parse/src_parser/find_type_node.c \
              src_parse/src_parser/parser.c \
              src_parse/src_parser/parser_parenthesis.c \
              src_parse/src_parser/parser_specific.c \
              src_parse/src_parser/parser_specific_2.c \
              src_parse/src_parser/parser_specific_3.c \
              src_parse/src_test/print_ast.c \
              src_parse/src_test/print_lst.c \
              src_parse/src_test/print_lst_tr.c \
              src_parse/src_test/print_str.c

PARSER_OBJS = $(patsubst %,$(OBJ_DIR)/parser/%,$(PARSER_SRCS:.c=.o))

# --------------------------
# PART 2: EXECUTOR
# --------------------------
EXEC_INCLUDE_FLAGS = -Iinclude -Iinclude/exec -Iinclude/parse -Ilib/libft/include
EXEC_CFLAGS = $(WARNING_FLAGS) $(EXEC_INCLUDE_FLAGS)

EXEC_SRCS = ast/ast_nodes.c \
            ast/ast_free.c \
            builtins/builtins.c \
            builtins/cd.c \
            builtins/echo.c \
            builtins/env.c \
            builtins/exit.c \
            builtins/export.c \
            builtins/export_utils.c \
            builtins/history.c \
            builtins/pwd.c \
            builtins/unset.c \
            env/env_build.c \
            env/env_export.c \
            env/env_temp_utils.c \
            env/env_envp_utils.c \
            exec/exec_ast.c \
            exec/exec_command.c \
            exec/exec_command_utils.c \
            exec/exec_heredoc.c \
            exec/exec_logic.c \
            exec/exec_path.c \
            exec/exec_pipe.c \
            exec/exec_redir.c \
            exec/exec_search.c \
            exec/exec_wildcard.c \
            utils/dup_argv.c \
            utils/var_utils.c \
            utils/clean.c \
            utils/utils.c

EXEC_OBJS = $(patsubst %,$(OBJ_DIR)/exec/%,$(EXEC_SRCS:.c=.o))

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# --------------------------
# LINK LINE
# --------------------------
LINK_LINE = $(CC) $(PARSER_CFLAGS) $(PARSER_OBJS) $(EXEC_CFLAGS) $(EXEC_OBJS) $(OBJ_DIR)/main.o $(OBJ_DIR)/global.o $(LIBFT) -lreadline -o $(NAME)

# --------------------------
# TARGETS
# --------------------------
all: minishell

minishell: check_libft $(OBJ_DIR)/main.o $(OBJ_DIR)/global.o $(PARSER_OBJS) $(EXEC_OBJS)
	@$(LINK_LINE)
	@echo "$(BOLD)$(WHITE)>> $(NAME) build successfully! 🎉$(RESET)"
	@touch .mandatory_compiled

build_all: $(PARSER_OBJS) $(EXEC_OBJS) $(OBJ_DIR)/main.o $(OBJ_DIR)/global.o
	@$(LINK_LINE)
	@echo "$(BOLD)$(WHITE)>> $(NAME) build successfully! 🎉$(RESET)"
	@touch .mandatory_compiled

# --------------------------
# Individual targets
# --------------------------
parser: check_libft
	@if [ -f .parser_compiled ]; then \
		echo "$(BOLD)$(WHITE)>> Parser already compiled ✔$(RESET)"; \
	else \
		$(MAKE) build_parser; \
	fi

exec: check_libft
	@if [ -f .exec_compiled ]; then \
		echo "$(BOLD)$(WHITE)>> Executor already compiled ✔$(RESET)"; \
	else \
		$(MAKE) build_exec; \
	fi

build_parser: $(PARSER_OBJS)
	@$(CC) $(PARSER_CFLAGS) $(PARSER_OBJS) src_parse/main.c $(LIBFT) -o parser.out
	@echo "$(BOLD)$(WHITE)>> Parser build successfully! 🎉$(RESET)"
	@touch .parser_compiled

build_exec: $(EXEC_OBJS)
	@$(CC) $(EXEC_CFLAGS) $(EXEC_OBJS) src_exec/main.c $(LIBFT) -o exec.out
	@echo "$(BOLD)$(WHITE)>> Executor build successfully! 🎉$(RESET)"
	@touch .exec_compiled

# --------------------------
# Rules for compiling .c -> .o
# --------------------------
$(OBJ_DIR)/parser/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)>> Compiling $<... $(BOLD)$(GREEN)[ OK ]$(RESET)"
	@$(CC) $(PARSER_CFLAGS) -c $< -o $@

$(OBJ_DIR)/exec/%.o: $(SRC_EXEC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)>> Compiling $<... $(BOLD)$(GREEN)[ OK ]$(RESET)"
	@$(CC) $(EXEC_CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: src/main.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)>> Compiling $<... $(BOLD)$(GREEN)[ OK ]$(RESET)"
	@$(CC) $(WARNING_FLAGS) $(PARSER_INCLUDE_FLAGS) $(EXEC_INCLUDE_FLAGS) -c $< -o $@

$(OBJ_DIR)/global.o: src/global.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)>> Compiling $<... $(BOLD)$(GREEN)[ OK ]$(RESET)"
	@$(CC) $(WARNING_FLAGS) $(PARSER_INCLUDE_FLAGS) $(EXEC_INCLUDE_FLAGS) -c $< -o $@

# --------------------------
# Libft check
# --------------------------
check_libft:
	@if [ -f .libft_compiled ]; then \
		echo "$(BOLD)$(WHITE)>> Libft already compiled ✔$(RESET)"; \
	elif [ ! -f $(LIBFT) ] || [ -n "$$(find $(LIBFT_DIR)/src -newer $(LIBFT))" ]; then \
		$(MAKE) -C $(LIBFT_DIR); \
		touch .libft_compiled; \
		echo "$(BOLD)$(GREEN)>> Libft built!$(RESET)"; \
	else \
		touch .libft_compiled; \
		echo "$(BOLD)$(WHITE)>> Libft is up to date ✔$(RESET)"; \
	fi

# --------------------------
# Clean
# --------------------------
clean:
	@echo -n "$(BOLD)$(WHITE)>> Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR) .mandatory_compiled .exec_compiled .parser_compiled .libft_compiled
	@$(MAKE) -C $(LIBFT_DIR) clean >/dev/null
	@echo "$(BOLD)$(GREEN) [ OK ]$(RESET)"

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo -n "$(BOLD)$(RED)>> Removing $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(BOLD)$(GREEN) [ OK ]$(RESET)"; \
	fi
	@if [ -f "parser.out" ]; then rm -f parser.out; fi
	@if [ -f "exec.out" ]; then rm -f exec.out; fi
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Phony
.PHONY: all minishell mandatory parser exec build_all build_parser build_exec clean fclean re check_libft
