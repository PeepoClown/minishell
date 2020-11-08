NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O2

HEADER_DIR = ./
INCLUDE = -I $(HEADER_DIR)

SRCS =	ft_strlen.c ft_strcmp.c ft_strdup.c \
		ft_substr.c ft_find_first_of.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_islowcase.c ft_isupcase.c \
		ft_isdigit.c ft_isalpha.c ft_isalnum.c \
		ft_atoi.c ft_strcpy.c ft_strjoin.c \
		ft_split.c ft_strtrim.c ft_strchr.c \
		ft_copy_char_matrix.c ft_remove_char_matrix.c ft_putnbr_fd.c \
		ft_itoa.c ft_tolower.c
SRC_DIR = ./
SRC = $(addprefix $(SRC_DIR), $(SRCS))

OBJS = $(SRC:.c=.o)
OBJ_DIR = ./
OBJ = $(addprefix $(OBJ_DIR), $(OBJS))

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)lib.h
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

norme :
	norminette .

.PHONY : all clean fclean re norme
