SRC =	./src/gnl/get_next_line.c \
	./src/gnl/get_next_line_fd.c \
	./src/env_cpy.c \
	./src/build_board.c \
	./src/ctrlc.c \
	./src/my.c \
	./src/main.c \
	./src/my_cd.c \
	./src/my_double_malloc.c \
	./src/my_exec_path.c \
	./src/my_getenv.c \
	./src/set_unsetenv.c \
	./src/replace_tilt.c \
	./src/res_not_finish.c \
	./src/del_alias_elem.c \
	./src/update_alias.c \
	./src/check_if_alias.c \
	./src/my_getnbr.c \
	./src/ini_struct.c \
	./src/check_if_redir.c \
	./src/build_board_case.c \
	./src/double_redir_left.c \
	./src/build_exec.c \
	./src/loop_elem.c \
	./src/all_for_pipes.c \
	./src/case_first_exec.c \
	./src/update_env.c

CFLAGS += -Wextra -Wall
CFLAGS += -pedantic
CFLAGS += -I./include

NAME =	lil_shell

RM =	rm -f

CC = gcc

OBJS=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
