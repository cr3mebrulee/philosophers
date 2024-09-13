/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:04 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 10:57:14 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				num;
	t_simulation	*sim;

	sim = malloc(sizeof(*sim));
	if (sim == NULL)
	{
		return (1);
	}
	num = sim->number_of_philos;
	if (!parse_arguments(argc, argv, sim))
		return (1);
	if (init_simulations(argc, argv, sim) != 0)
		return (1);
	if (allocate_memory(sim) != 0)
		return (1);
	init_philos(sim);
	if (init_mutexes(sim) != 0)
		return (1);
	if (create_threads(sim) != 0)
		return (1);
	join_threads(sim);
	destroy_mutexes(sim, num, num, true, true);
	free_memory(sim);
	return (0);
}
