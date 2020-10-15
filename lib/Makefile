NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O2

HEADER_DIR = ./
INCLUDE = -I $(HEADER_DIR)

SRCS =	ft_strlen.c ft_strcmp.c ft_strdup.c \
		ft_substr.c ft_find_first_of.c ft_putstr_fd.c \
		ft_putendl_fd.c
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
