/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:04 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/07 14:59:51 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (!parse_arguments(argc, argv))
		return (1);
	if (initialise_simulations(argc, argv, &sim) != 0)
	{
		printf("Error: Failed to initialize simulation\n");
		return (1);
	}
	if (initialize_philosophers_and_forks(&sim) != 0)
	{
		printf("Error: Failed to initialize philosophers and forks.\n");
		return (1);
	}
	if (pthread_mutex_init(&sim.print_lock, NULL) != 0)
	{
		printf("Error: Failed to initialize print mutex.\n");
		initiate_termination(&sim, 1, 1, 0);
		return (1);
	}
	if (create_threads(&sim) != 0)
		return (1);
	initiate_termination(&sim, 1, 1, 1);
	return (0);
}
