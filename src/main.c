/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:04 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 15:58:33 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* ++ parse argunents and initiate simulation with parsed arguments*/
/*initiate philosophers*/
/*initiate mutexes*/
/*create threads for each philosopher*/
/*create threads to monitor death*/
/*create thread to monitor meals amount*/
/*join threads*/
/*release resources*/
/*error handling*/

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (!parse_arguments(argc, argv))
		return (1);
	if (init_simulations(argc, argv, &sim) != 0)
		return (1);
	if (allocate_memory(&sim) != 0)
	{
		return (1);
	}
	if (init_philos(&sim) != 0)
	{
		return (1);
	}
	if (init_mutexes(&sim) != 0)
	{
		free_resources(&sim, 1, 1);
		return (1);
	}
	print_simulation(&sim);
	print_philosopher_info(&sim, sim.number_of_philos);
	if (create_threads(&sim) != 0)
	{
		free_resources(&sim, 1, 1);
		return (1);
	}
	join_threads(&sim);
	free_resources(&sim, 1, 1);
	return (0);
}
