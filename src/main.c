/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:04 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:32 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_simulation	*sim;
	t_mutex_info	*mutex_info;

	sim = malloc(sizeof(*sim));
	if (sim == NULL)
		return (1);
	mutex_info = malloc(sizeof(t_mutex_info));
	if (mutex_info == NULL)
		return (1);
	if (parse_arguments(argc, argv, sim, mutex_info) != 0)
		return (1);
	if (init_simulations(argc, argv, sim, mutex_info) != 0)
		return (1);
	if (allocate_memory(sim, mutex_info) != 0)
		return (1);
	init_philos(sim);
	if (init_mutexes(sim, mutex_info) != 0)
		return (1);
	if (create_threads(sim, mutex_info) != 0)
		return (1);
	join_threads(sim);
	destroy_mutexes(sim, mutex_info);
	free_memory(sim, mutex_info);
	return (0);
}
