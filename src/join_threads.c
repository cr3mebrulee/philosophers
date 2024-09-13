/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:50:41 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/12 20:23:29 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_philos_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
		{
			printf("Error: Failed to join philosopher thread %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_monitor_thread(t_simulation *sim)
{
	if (pthread_join(sim->monitor_thread, NULL) != 0)
	{
		printf("Error: Failed to join monitor thread\n");
		return (1);
	}
	return (0);
}

int	join_threads(t_simulation *sim)
{
	if (join_philos_threads(sim) != 0)
	{
		return (1);
	}
	if (join_monitor_thread(sim) != 0)
	{
		return (1);
	}
	return (0);
}
