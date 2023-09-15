GREEN		= 	\033[0;32m
RED			= 	\033[0;31m
RESET		= 	\033[0m

NAME		=	minishell

LFT			=	libft/obj libft/libft.a

HEADER		=	./includes -I ./libft/includes

OBJ			=	$(patsubst src%, obj%, $(SRC:.c=.o))

SRC			=	src/minishell.c \
				src/parse/utils.c \
				src/parse/utils2.c \
				src/parse/utils3.c \
				src/parse/utils4.c \
				src/parse/utils5.c \
				src/parse/init_parse.c \
				src/parse/parse_utils.c \
				src/parse/parse_quotes.c \
				src/execution/cmds.c \
				src/execution/free.c \
				src/execution/utils.c \
				src/execution/get_path.c \
				src/execution/fd_checker.c \
				src/execution/fd_heredoc.c \
				src/execution/generate_cmd.c \
				src/execution/generate_cmd2.c \
				src/builtins/ft_cd.c \
				src/builtins/ft_pwd.c \
				src/builtins/ft_env.c \
				src/builtins/ft_exit.c \
				src/builtins/ft_echo.c \
				src/builtins/ft_unset.c \
				src/builtins/ft_export.c \
				src/builtins/msg_error.c \
				src/builtins/check_builtins.c

CC			=	cc
FLAGS		=	-I${HEADER} -Wall -Wextra -Werror -g

all:		$(LFT) obj $(NAME) 

$(NAME):	$(OBJ)
			@$(CC) -o $@ $^ $(FLAGS) -lreadline -L ./libft -lft

$(LFT):		
			@@echo " [ .. ] | Compiling libft.."
			@$(MAKE) -C libft -f Makefile all --no-print-directory
			@@echo " [ $(GREEN)OK$(RESET) ] | Libft ready!"

obj:
			@mkdir -p obj/parse obj/execution obj/builtins

obj/%.o:	src/%.c ./includes/minishell.h
			@$(CC) $(FLAGS) -o $@ -c $<
			@echo "$@ $(GREEN)created$(RESET)"

valgrind:	all
			valgrind --leak-check=full --show-leak-kinds=all ./minishell

clean:
			@rm -rf $(OBJ) obj
			@$(MAKE) -C libft -f Makefile clean --no-print-directory
			@echo "Object files $(RED)removed.$(RESET)"

fclean:		clean
			@rm -rf $(NAME)
			@$(MAKE) -C libft -f Makefile fclean --no-print-directory

re:			fclean all

.PHONY:		all clean fclean re