NAME = minishell
CFLAGS = -g -O2 -Wall -Werror -Wextra

HEADERS = minishell.h
HEADER_DIR = include/
HEADER = $(addprefix $(HEADER_DIR), $(HEADERS))
INCLUDE = -I $(HEADER_DIR)

LIB_DIR = lib/
LIB_LINK = -lft
LINK = -L. $(LIB_LINK)

SRCS =	main.c \
		\
		engine/builtin.c engine/cmd.c engine/error.c \
		engine/open_redirections.c engine/programm_params.c engine/programm.c \
		engine/prompt.c engine/signals.c engine/validate_cmd.c \
		engine/validate_redirections.c engine/input.c engine/validate_hidden_env.c \
		\
		cmd/ft_cd.c cmd/ft_echo.c cmd/ft_env.c \
		cmd/ft_exit.c cmd/ft_export.c cmd/ft_pwd.c \
		cmd/ft_unset.c \
		\
		env/add_env.c env/create_env.c env/del_env.c \
		env/get_env_matrix.c env/get_env_value.c env/print_env.c \
		env/remove_env.c env/sort_env.c env/change_env_value.c \
		env/copy_env.c \
		\
		parser/lexer.c parser/parser.c parser/quoting.c \
		parser/utils_01.c parser/utils_02.c parser/tokens.c \
		parser/quoting_env.c parser/lexer_validate.c parser/lexer_errors.c
SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJS = $(SRC:.c=.o)
OBJ_DIR = ./
OBJ = $(addprefix $(OBJ_DIR), $(OBJS))

.PHONY : all
all : $(NAME)

$(NAME) : $(OBJ)
	@$(MAKE) all -C $(LIB_DIR)
	@cp $(LIB_DIR)libft.a ./
	@gcc $(CFLAGS) $(OBJ) $(LINK) -o $(NAME)

%.o : %.c $(HEADER)
	gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY : clean
clean :
	@$(MAKE) clean -C $(LIB_DIR)
	@rm -rf $(OBJ)

.PHONY : fclean
fclean : clean
	@$(MAKE) fclean -C $(LIB_DIR)
	@rm -rf libft.a $(NAME)

.PHONY : re
re : fclean all
