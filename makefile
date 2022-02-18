NAME        =   philo

CC			=	clang

FLAG		=	-Wall -Wextra -Werror -fsanitize=thread

THREAD_F	=	-lpthread

C_FILE		=	main.c			\
				philosopher.c	\
				function.c		\
				liste.c			\
				protect.c		\
				routine.c		\
				monitoring.c	\

C_DIR		=	./src/

SRC			=	$(addprefix $(C_DIR), $(C_FILE))

OBJ			=	$(SRC:.c=.o)

INCLUDE		=	philo.h

I_DIR		=	./include/

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) $(OBJ) $(THREAD_F) -o $(NAME)
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re all clean fclean
