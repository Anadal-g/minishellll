NAME = libft.a

CFLAGS = -Wall -Werror -Wextra
CC = cc
AR = ar -crs
RM = rm -f

SRCS = $(addprefix ./lib/, ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_atol.c ft_strcmp.c ft_strcat.c ft_realloc.c ft_strndup.c ft_strcpy.c)
		

SRCS_GNL = $(addprefix ./gnl/, get_next_line.c get_next_line_utils.c)

SRCS_PRINTF = $(addprefix ./ft_printf/, ft_printf_basics.c ft_printf_others.c ft_printf.c)
		
SRCS_BONUS = $(addprefix ./bonus/, ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
				ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c)

SRCS_ADDITIONAL = $(addprefix ./additional/, free_matrix.c ft_strchr_bool.c \
					nodes.c free_matrix_bool.c character_finder.c jump_character.c \
					is_redir.c )

OBJS = $(SRCS:.c=.o)
OBJS_GNL = $(SRCS_GNL:.c=.o)
OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_ADDITIONAL = $(SRCS_ADDITIONAL:.c=.o)

OBJS_ALL = $(OBJS) $(OBJS_BONUS) $(OBJS_GNL) $(OBJS_PRINTF) $(OBJS_ADDITIONAL)

all : $(NAME)

$(NAME) : $(OBJS_ALL)
	$(AR) $(NAME) $(OBJS_ALL)
	
clean:
	$(RM) $(OBJS_ALL)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re