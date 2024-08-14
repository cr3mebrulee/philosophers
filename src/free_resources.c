/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:34:18 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 12:07:24 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destroy_time_lock(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_destroy(&sim->philos[i].time_lock);
		i++;
	}
	return ;
}

void	destroy_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	return ;
}

// void	join_all_threads(t_simulation *sim)
// {
// 	int	i;

// 	i = 0;
// 	while (i < sim->number_of_philos)
// 	{
// 		pthread_join(sim->threads[i], NULL);
// 		i++;
// 	}
// }

void	initiate_termination(t_simulation *sim, int f_f, int m_f, int pr_f)
{
	//join_all_threads(sim);
	if (f_f == 1)
	{
		destroy_forks(sim);
	}
	if (m_f == 1)
	{
		pthread_mutex_destroy(&sim->print_lock);
	}
	if (pr_f)
	{
		destroy_time_lock(sim);
	}
	free_resources(sim);
}

void	free_resources(t_simulation *sim)
{
	free(sim->philos);
	free(sim->forks);
	return ;
}
