/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:28:53 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 12:32:37 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_monitor_thread(t_simulation *sim)
{
	int result;

    // Ensure sim is not null
    if (!sim)
    {
        printf("Error: Simulation struct is null\n");
        return (1);
    }
    // Attempt to create the monitor thread
    result = pthread_create(&(sim->monitor_thread), NULL, monitor, (void *)sim);
    if (result != 0)
    {
        printf("Error: Failed to create monitor thread, error code: %d\n", result);
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
		//sim->philos[i].last_meal_time = current_timestamp();
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

int	create_threads(t_simulation *sim)
{
	if (create_philos_thread(sim) != 0)
	{
		return (1);
	}
	if(create_monitor_thread(sim) != 0)
	{
		//join_philos_thread(sim);
		return (1);
	}
	return (0);
}
