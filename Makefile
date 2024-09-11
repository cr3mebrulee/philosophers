NAME	= philo
LIBFT	= ./libft/libft.a

SRCS 	= src/main.c\
					src/parse_arguments.c\
					src/init_simulations.c\
					src/allocate_memory.c\
					src/init_philos_and_mutexes.c\
					src/create_threads.c\
					src/routine.c\
					src/debugging_functions.c\
					src/free_resources.c\
					src/current_time.c\
					src/monitor.c

OBJS 	= ${SRCS:.c=.o}

HEADER	= -I include

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g

all: 	libft	${NAME}

%.o: %.c
	@echo "\033[33m----Compiling ${@}----"
	@$(CC) ${CFLAGS} ${HEADER} -c $< -o $@

${NAME}:	${OBJS} ${LIBFT}
					@echo "\033[33m----Compiling philosophers binary----\033[0m"
					@$(CC) ${OBJS} -Llibft -lft -o ${NAME}

libft:
	@make -C ./libft

clean:
					@make clean -C ./libft
					@rm -f ${OBJS}

fclean: 	clean
					@make fclean -C ./libft
					@rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re    libft
