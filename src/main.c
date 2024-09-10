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

#include "../include/philosophers.h"

void	print_philosopher_info(t_simulation *sim, int num)
{
	int	i;
	//t_philosopher *philos;

	for (i = 0; i < num; i++)
	{
		printf("Philosopher %d:\n", sim->philos[i].id);
		printf("ID of philosopher: %d\n", sim->philos[i].id);
		printf("Meals eaten: %d\n", sim->philos[i].meals_eaten);
		printf("Last meal time: %lld\n", sim->philos[i].last_meal_time);
		printf("Left fork: %p\n", (void *)sim->philos[i].left_fork);
		printf("Right fork: %p\n", (void *)sim->philos[i].right_fork);
		printf("Simulation: %p\n", (void *)sim->philos[i].sim);
		printf("\n");
	}
}

/* ++ parse argunents and initiate simulation with parsed arguments*/
/*initiate philosophers*/
/*initiate mutexes*/
/*create threads for each philosopher*/
/*create threads to monitor death*/
/*create thread to monitor meals amount*/
/*join threads*/
/*release resources*/
/*error handling*/

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

int	main(int argc, char **argv)
{
	t_simulation	*sim;

	sim = malloc(sizeof(*sim));
	if (sim == NULL)
	{
		return (1);
	}
	if (!parse_arguments(argc, argv))
		return (1);
	if (init_simulations(argc, argv, sim) != 0)
		return (1);
	if (allocate_memory(sim) != 0)
	{
		return (1);
	}
	if (init_philos(sim) != 0)
	{
		return (1);
	}
	if (init_mutexes(sim) != 0)
	{
		free_resources(sim, 1, 1);
		return (1);
	}
	print_simulation(sim);
	print_philosopher_info(sim, sim->number_of_philos);
	if (create_threads(sim) != 0)
	{
		//free_resources(&sim, 1, 1);
		return (1);
	}
	// Let main function to wait for philosopher threads finishing work
	if (join_philos_threads(sim) != 0)
	{
		printf("Error: Failed to join philosopher threads\n");
		return (1);
	}
	// Join monitor thread
	if (join_monitor_thread(sim) != 0)
	{
		printf("Error: Failed to join monitor thread\n");
		return (1);
	}
	free_resources(sim, 1, 1);
	free(sim);
	return (0);
}
