/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:28:53 by taretiuk          #+#    #+#             */
/*   Updated: 2024/07/31 16:26:53 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void check_meal_counts(t_simulation *sim)
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
	// If all philosophers have eaten the required number of meals, end the simulation
	if (all_philos_done)
	{
		pthread_mutex_lock(&sim->print_lock);
		printf("All philosophers have eaten %d times\n", sim->number_of_meals);
		pthread_mutex_unlock(&sim->print_lock);
		free(sim->philos);
		free(sim->forks);
		exit (0); // Terminate simulation
	}
}

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->number_of_philos)
		{
			pthread_mutex_lock(&sim->philos[i].meal_time_lock);
			//checks if the philosopher starving
			if (current_timestamp() - sim->philos[i].last_meal_time > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->print_lock);
				printf("%lld %d died\n", current_timestamp(), sim->philos[i].id);
				pthread_mutex_unlock(&sim->print_lock);
				exit(0); // Terminate simulation
			}
			pthread_mutex_unlock(&sim->philos[i].meal_time_lock);
			i++;
		}
		//Check if philosophers ate all specified number of time
		check_meal_counts(sim);
		usleep(1000);
	}
	return (NULL);
}

int	wait_threads(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
		{
			printf("Failed to join thread");
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_simulation *sim)
{
	int	i;
	int	num;
	pthread_t	monitor_thread;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, routine,
				(void *)&sim->philos[i]) != 0)
		{
			printf("Failed to create thread");
			destroy_mutexes(sim);
			free_resources(sim);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, (void *)sim) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		destroy_mutexes(sim);
		free_resources(sim);
		return (1);
	}
	if (wait_threads(sim) != 0)
	{
		return (1);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		printf("Failed to join monitor thread\n");
		return (1);
	}
	return (0);
}
