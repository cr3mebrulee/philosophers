/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:20:15 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 17:29:12 by taretiuk         ###   ########.fr       */
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

# define USAGE_MESSAGE "\
Usage: number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef enum e_enumeration
{
	DEAD,
	ALIVE,
	SATISFIED
}	t_philosopher_status;

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	int					if_alive;
	int					start_time;
	long long int		meal_time;
	pthread_mutex_t		*left_fork; // lock for the 1st fork
	pthread_mutex_t		*right_fork; // lock for the 2nd fork
	pthread_mutex_t		time_lock; // lock for meal_time
	struct s_simulation	*simulation;
	t_philosopher		status;
}	t_philosopher;

typedef struct s_simulation
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	int					stop_simulation;
	int					satrt_time;
	pthread_t			*thread;
	pthread_mutex_t		*forks; // lock for array of forks
	pthread_mutex_t		print_lock; // lock to print
	t_philosopher		*philos;
}	t_simulation;

void		print_simulation(t_simulation *sim);
int			is_number(const char *str);
int			parse_arguments(int argc, char **argv);
int			init_simulations(int argc, char **argv, t_simulation *sim);
int			init_philos_and_forks(t_simulation *sim);
long long	current_timestamp(void);
void		monitor_state(t_simulation *sim, char active);
int			create_threads(t_simulation *sim);
void		initiate_termination(t_simulation *sim, int f_f, int m_f, int pr_f);
void		free_resources(t_simulation *sim);
void		destroy_forks(t_simulation *sim);
void		destroy_meal_time_lock(t_simulation *sim);
void		*routine(void *arg);

#endif
