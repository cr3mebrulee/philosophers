NAME	= philo
LIBFT	= ./libft/libft.a

SRCS 	= src/main.c\
					src/parse_arguments.c\
					src/initialise_simulations.c\
					src/initialize_philosophers_and_forks.c\
					src/routine.c\
					src/free_resources.c\
					src/create_threads.c\
					src/monitor.c\
					src/responsive_sleep.c\
					src/monitor_death.c

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
