# NAME
NAME = minishell

# SOURCE FILES
SRC_DIR		=	src/

SRC_FILES	=	minishell.c \
				built-ins/core_builtins.c \
				built-ins/echo.c \
				built-ins/cd.c \
				built-ins/pwd.c \
				built-ins/export.c \
				built-ins/unset.c \
				built-ins/env.c \
				built-ins/exit.c \
				built-ins/history.c \
				env/env_manager.c \
				env/env_utils.c \
				exec/redirections_utils.c \
				exec/executor.c \
				exec/exec_errors.c \
				exec/exec_one_cmd.c \
				exec/childs.c \
				exec/last_childs.c \
				exec/heredoc.c \
				exec/manage_infile.c \
				exec/manage_outfile.c \
				exec/path.c \
				exec/utils_exec.c \
				exec/parsing_redir.c \
				exec/redir.c \
				parsing/redir_utils.c \
				parsing/quotes/quote_handler.c \
				parsing/quotes/quote_parser.c \
				parsing/command_list.c \
				parsing/errors.c \
				parsing/expansor.c \
				parsing/frees.c \
				parsing/lexer.c \
				parsing/parsing.c \
				parsing/utils_stack.c \
				utils/utils.c \
				utils/syntax_pipe.c \
				signals/signals.c 

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

# OBJECT FILES
OBJ_DIR		= objs/
OBJ_FILES 	= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# COMPILER
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3

# Para sistemas con readline instalado vía Homebrew (como Mac M1/M2/M3)
CFLAGS	+= -I/opt/homebrew/opt/readline/include
LDFLAGS	= -L/opt/homebrew/opt/readline/lib -lreadline

INCLUDE	= -I includes
RM		= rm -rf
LIBFT	= libft/libft.a

# COLORS
RED		= \033[91;1m
GREEN	= \033[92;1m
YELLOW	= \033[93;1m
BLUE	= \033[94;1m
PINK	= \033[95;1m
CLEAR	= \033[0m

# MAKEFILE RULES
all: $(NAME)

$(NAME): $(OBJ_FILES)
	@make -sC libft
	@echo "$(GREEN)\nCompiling the minishell program.$(CLEAR)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(INCLUDE) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)	      [OK]\n$(CLEAR)$(GREEN)      	    Success!$(CLEAR)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)\nRemoving compiled files.$(CLEAR)"
	@$(RM) $(OBJ_DIR)
	@make clean -sC libft
	@echo "$(RED)	[OK]\n$(CLEAR)$(RED)      Success!$(CLEAR)\n"
	@echo "$(RED)Object files removed correctly\n$(CLEAR)"

fclean:
	@make clean >/dev/null 2>&1
	@echo "$(RED)\nRemoving exec. files.$(CLEAR)"
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "$(RED)	[OK]\n$(CLEAR)$(RED)      Success!$(CLEAR)\n"
	@echo "$(RED)Everything removed correctly\n$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re
