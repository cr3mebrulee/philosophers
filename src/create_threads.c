/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:28:53 by taretiuk          #+#    #+#             */
/*   Updated: 2024/07/29 15:32:58 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
			if (current_timestamp() - sim->philos[i].last_meal_time > sim->time_to_die)
			{
				pthread_mutex_lock(&sim->print_lock);
				ft_printf("Philosopher %d has died\n", sim->philos[i].id);
				pthread_mutex_unlock(&sim->print_lock);
				exit(0); // Terminate simulation
			}
			pthread_mutex_unlock(&sim->philos[i].meal_time_lock);
			i++;
		}
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
			ft_printf("Failed to join thread");
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
			ft_printf("Failed to create thread");
			destroy_mutexes(sim);
			free_resources(sim);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, (void *)sim) != 0)
	{
		ft_printf("Error: Failed to create monitor thread\n");
		destroy_mutexes(sim);
		free_resources(sim);
		return (1);
	}
	wait_threads(sim);
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		ft_printf("Failed to join monitor thread\n");
		return (1);
	}
	return (0);
}
