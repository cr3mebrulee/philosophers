/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:20:15 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 14:43:39 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "../libft/libft.h"
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

# define USAGE_MESSAGE "\
Usage:\n\
number_of_philosophers	The number of philosophers\n\
time_to_die               Time (in ms) until a philosopher dies if not fed\n\
time_to_eat               Time (in ms) a philosopher takes to eat\n\
time_to_sleep             Time (in ms) a philosopher sleeps\n\
[number_of_times_each_philosopher_must_eat] (optional)\n"

typedef enum e_enumeration
{
	DEAD,
	ALIVE,
	SATISFIED,
	STARVING
}	t_philosopher_status;

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	int					on_fork;
	long long			last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		time_lock;
	struct s_simulation	*sim;
	pthread_t			thread;
}	t_philosopher;

typedef struct s_simulation
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	volatile int		if_alive;
	volatile int		satisfaction;
	pthread_t			monitor_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print_lock;
	pthread_mutex_t		*state;
	t_philosopher		*philos;
}	t_simulation;

typedef struct s_mutex_info
{
	int		num_forks;
	int		num_times;
	bool	print_lock_init;
	bool	state_lock_init;
}	t_mutex_info;

int			parse_arguments(int argc, char **argv, t_simulation *sim,
				t_mutex_info *mutex_info);
int			is_number(const char *str);
int			init_simulations(int argc, char **argv, t_simulation *sim,
				t_mutex_info *mutex_info);
int			init_mutexes(t_simulation *sim, t_mutex_info *mutex_info);
int			allocate_memory(t_simulation *sim, t_mutex_info *mutex_info);
int			init_philos(t_simulation *sim);
void		*monitor(void *arg);
void		*routine(void *arg);
void		print_message(t_philosopher *philo, const char *message);
void		release_mutexes(t_philosopher *philo);
void		precise_sleep(int ms);
long long	current_time(void);
int			create_threads(t_simulation *sim, t_mutex_info *mutex_info);
int			join_threads(t_simulation *sim);
void		free_structures(t_simulation *sim, t_mutex_info *mutex_info);
void		free_memory(t_simulation *sim, t_mutex_info *mutex_info);
void		destroy_mutexes(t_simulation *sim, t_mutex_info *mutex_info);

#endif
