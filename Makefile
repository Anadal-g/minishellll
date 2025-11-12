#NAME
NAME = minishell

# SOURCE FILES
SRC_DIR		=	src/

SRC_FILES	=	main/minishell.c \
				main/utils_main.c \
				built-ins/core_builtins.c \
				built-ins/echo.c \
				built-ins/cd.c \
				built-ins/pwd.c \
				built-ins/export.c \
				built-ins/export_2.c \
				built-ins/export_3.c \
				built-ins/unset.c \
				built-ins/env.c \
				built-ins/exit.c \
				built-ins/history.c \
				env/env_manager.c \
				env/env_utils.c \
				exec/redirections_utils.c \
				exec/executor.c \
				exec/executor_2.c \
				exec/exec_errors.c \
				exec/exec_one_cmd.c \
				exec/childs.c \
				exec/last_childs.c \
				exec/heredoc.c \
				exec/manage_infile.c \
				exec/manage_outfile.c \
				exec/path.c \
				exec/path_2.c \
				exec/utils_exec.c \
				exec/parsing_redir.c \
				exec/redir.c \
				exec/redir_2.c \
				parsing/redir_utils.c \
				parsing/quotes/quote_handler.c \
				parsing/quotes/quote_parser.c \
				parsing/command_list.c \
				parsing/errors.c \
				parsing/other_utils.c \
				parsing/expansor.c \
				parsing/frees.c \
				parsing/lexer.c \
				parsing/parsing.c \
				parsing/utils_stack.c \
				utils/utils.c \
				utils/utils_2.c \
				utils/syntax_pipe.c \
				signals/signals.c 

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

#OBJECT FILES
OBJ_DIR		= objs/
OBJ_FILES 	= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#COMPILER
CC		= cc
FLAGS	= -Wall -Wextra -Werror  -g3#-fsanitize=address
LDFLAGS = -lreadline
INCLUDE	= -I includes
RM		= rm -rf
LIBFT	= libft/libft.a

# READLINE_DIR = $(shell brew --prefix readline)
# FLAGS += -I$(READLINE_DIR)/include
# LDFLAGS += -L$(READLINE_DIR)/lib -lreadline

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

#MAKEFILE RULES
all: $(NAME)

$(NAME) : $(OBJ_FILES)
	@make -sC libft
	@echo "$(GREEN)\nCompiling the minishell program.$(CLEAR)"
	@$(CC) $(FLAGS) $(OBJ_FILES) $(INCLUDE) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)	      [OK]\n$(CLEAR)$(GREEN)      	    Success!$(CLEAR)\n"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@
	
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
