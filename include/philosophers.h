/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:20:15 by taretiuk          #+#    #+#             */
/*   Updated: 2024/07/29 16:10:39 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define	PHILO_H

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

typedef struct s_philosopher
{
	int	id;
	int	meals_eaten;
	long long	last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t thread;
	struct s_simulation	*simulation;
	pthread_mutex_t	meal_time_lock;
}	t_philosopher;

typedef struct s_simulation
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
	int	stop_simulation;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	t_philosopher		*philos;
}	t_simulation;

void	print_simulation(t_simulation *sim);
int		is_number(const char *str);
int		parse_arguments(int argc, char **argv);
int		initialise_simulations(int argc, char **argv, t_simulation *sim);
int		initialize_philosophers_and_forks(t_simulation *sim);
void	print_philosopher_info(t_philosopher *philos, int num);
void	destroy_mutexes(t_simulation *sim);
long long	current_timestamp(void);
int		create_threads(t_simulation *sim);
int		wait_threads(t_simulation *sim);
void	free_resources(t_simulation *sim);
void	*routine(void *arg);

#endif
