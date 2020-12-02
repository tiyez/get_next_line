
NAME=libgnl.a

SRC=\
get_next_line.c\
get_next_line_utils.c
OBJ=$(SRC:.c=.o)
CFLAGS=-O2

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $?

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
