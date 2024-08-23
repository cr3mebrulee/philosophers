/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:20:15 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/23 18:08:24 by taretiuk         ###   ########.fr       */
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

# define USAGE_MESSAGE "\
Usage: number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef enum e_enumeration
{
	DEAD,
	ALIVE,
	SATISFIED
}	t_philosopher_status;

//Storage of uniq data for each philosopher
typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	int					if_alive;
	int					status;
	long long			last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		time_lock;
	struct s_simulation	*sim;
	pthread_t			thread;
}	t_philosopher;

//Storage of the information shared by all philosophers
typedef struct s_simulation
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	pthread_t			monitor_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	t_philosopher		*philos;
}	t_simulation;

void		print_simulation(t_simulation *sim);
int			is_number(const char *str);
int			parse_arguments(int argc, char **argv);
int			init_simulations(int argc, char **argv, t_simulation *sim);
int			init_mutexes(t_simulation *sim);
int			init_philos(t_simulation *sim);
int			allocate_memory(t_simulation *sim);
void		precise_sleep(int ms);
long long	current_time(void);
void 		*monitor(void *arg);
void		*routine(void *arg);
void		print_philosopher_info(t_simulation *sim, int num);
void		print_simulation(t_simulation *sim);
int			create_threads(t_simulation *sim);
int 		join_threads(t_simulation *sim);
void		initiate_termination(t_simulation *sim, int f_f, int m_f, int pr_f);
int 		free_resources(t_simulation *sim, int forks, int philos);

#endif
