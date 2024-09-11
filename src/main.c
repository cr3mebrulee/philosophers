/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:04 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/23 18:25:14 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_philos_threads(t_simulation *sim)
{
	int	i;

	for (i = 0; i < sim->number_of_philos; i++)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
		{
			printf("Error: Failed to join philosopher thread %d\n", i);
			return (1);
		}
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

int	main(int argc, char **argv)
{
	t_simulation	*sim;

	sim = malloc(sizeof(*sim));
	if (sim == NULL)
	{
		return (1);
	}
	if (!parse_arguments(argc, argv))
	{
		free(sim);
		return (1);
	}
	if (init_simulations(argc, argv, sim) != 0)
	{
		free(sim);
		return (1);
	}
	if (allocate_memory(sim) != 0)
	{
		free_memory(sim);
		return (1);
	}
	init_philos(sim);
	if (init_mutexes(sim) != 0)
	{
		free_memory(sim);
		return (1);
	}
	if (create_threads(sim) != 0)
	{
		free_memory(sim);
		return (1);
	}
	if (join_threads(sim) != 0)
	{
		free_memory(sim);
		return (1);
	}
	destroy_mutexes(sim, sim->number_of_philos, true, true);
	free_memory(sim);
	return (0);
}
