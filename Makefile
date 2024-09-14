NAME	= philo

SRCS 	= src/main.c\
					src/parse_arguments.c\
					src/init_simulations.c\
					src/allocate_memory.c\
					src/init_philos.c\
					src/init_mutexes.c\
					src/create_threads.c\
					src/routine.c\
					src/print_message.c\
					src/release_mutexes.c\
					src/free_memory.c\
					src/destroy_mutexes.c\
					src/join_threads.c\
					src/current_time.c\
					src/monitor.c

OBJS    = ${SRCS:.c=.o}

HEADER  = -I include

CC      = cc
CFLAGS  = -Wall -Werror -Wextra -g -fsanitize=thread ${HEADER}

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lpthread

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
