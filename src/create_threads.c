/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:28:53 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/07 16:42:13 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_monitor_thread(pthread_t	*monitor_thread, t_simulation *sim)
{
	if (pthread_create(monitor_thread, NULL, monitor, (void *)sim) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		initiate_termination(sim, 1, 1, 1);
		exit (0);
	}
	return (0);
}

int	create_routine_thread(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, routine,
				(void *)&sim->philos[i]) != 0)
		{
			printf("Error: Failed to create routine thread");
			initiate_termination(sim, 1, 1, 1);
			exit (0);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_simulation *sim)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	create_routine_thread(sim);
	create_monitor_thread(&monitor_thread, sim);
	while (i < sim->number_of_philos)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
		{
			printf("Failed to join thread");
			initiate_termination(sim, 1, 1, 1);
			return (1);
		}
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		printf("Failed to join monitor thread\n");
		initiate_termination(sim, 1, 1, 1);
		return (1);
	}
	return (0);
}
