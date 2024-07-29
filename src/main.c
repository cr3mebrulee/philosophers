/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:04 by taretiuk          #+#    #+#             */
/*   Updated: 2024/07/29 16:27:00 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (!parse_arguments(argc, argv))
	{
		return (1);
	}
	if (initialise_simulations(argc, argv, &sim) != 0)
	{
		printf("Error: Failed to initialize simulation\n");
		return (1);
	}
	if (initialize_philosophers_and_forks(&sim) != 0)
	{
		ft_printf("Error: Failed to initialize philosophers and forks.\n");
		free_resources(&sim);
		return (1);
	}
	if (pthread_mutex_init(&sim.print_lock, NULL) != 0)
	{
		ft_printf("Error: Failed to initialize print mutex.\n");
		free_resources(&sim);
		return (1);
	}
	// print_simulation(&sim);
	// print_philosopher_info(sim.philos, sim.number_of_philos);
	if (create_threads(&sim) != 0)
	{
		return (1);
	}
	destroy_mutexes(&sim);
	free(sim.forks);
	free(sim.philos);
	return (0);
}
