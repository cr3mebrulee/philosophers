/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:28:53 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:55 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	create_monitor_thread(t_simulation *sim)
{
	int	result;

	if (!sim)
	{
		printf("Error: Simulation struct is null\n");
		return (1);
	}
	result = pthread_create(&(sim->monitor_thread), NULL, monitor, (void *)sim);
	if (result != 0)
	{
		printf("Error %d: Failed to create monitor thread\n", result);
		return (1);
	}
	return (0);
}

int	create_philos_thread(t_simulation *sim)
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
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_simulation *sim, t_mutex_info *mutex_info)
{
	if (create_philos_thread(sim) != 0)
	{
		destroy_mutexes(sim, mutex_info);
		free_memory(sim, mutex_info);
		return (1);
	}
	if (create_monitor_thread(sim) != 0)
	{
		destroy_mutexes(sim, mutex_info);
		free_memory(sim, mutex_info);
		return (1);
	}
	return (0);
}
