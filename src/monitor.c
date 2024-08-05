/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:24:10 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/05 16:40:56 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitor(void *arg);

void	check_meal_counts(t_simulation *sim)
{
	int	i;
	int	all_philos_done;

	i = 0;
	all_philos_done = 1;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_lock(&sim->philos[i].meal_time_lock);
		if (sim->philos[i].meals_eaten < sim->number_of_meals)
		{
			all_philos_done = 0;
		}
		pthread_mutex_unlock(&sim->philos[i].meal_time_lock);
		i++;
	}
	if (all_philos_done)
	{
		free(sim->philos);
		free(sim->forks);
		exit (0);
	}
}

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				i;
	long long int	current_time;
	long long int	print_time;

	sim = (t_simulation *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->number_of_philos)
		{
			pthread_mutex_lock(&sim->philos[i].meal_time_lock);
			current_time = current_timestamp() - sim->philos[i].last_meal_time;
			if (current_time > sim->time_to_die)
			{
				print_time = current_timestamp() - sim->philos[i].last_meal_time;
				pthread_mutex_lock(&sim->print_lock);
				printf("Philo %d died at %lld ms, message printed at %lld ms, ",
					sim->philos[i].id, current_time, print_time);
				printf("delay: %lld ms\n", print_time - current_time);
				pthread_mutex_unlock(&sim->print_lock);
				destroy_mutexes(sim);
				free_resources(sim);
				exit (0);
			}
			pthread_mutex_unlock(&sim->philos[i].meal_time_lock);
			i++;
		}
		check_meal_counts(sim);
		usleep(1000);
	}
	return (NULL);
}
