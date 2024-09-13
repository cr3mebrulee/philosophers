/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:34:18 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 13:42:56 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_structures(t_simulation *sim, t_mutex_info *mutex_info)
{
	if (sim)
	{
		free(sim);
		sim = NULL;
	}
	if (mutex_info)
	{
		free(mutex_info);
		mutex_info = NULL;
	}
}

void	free_memory(t_simulation *sim, t_mutex_info *mutex_info)
{
	if (sim->forks)
	{
		free(sim->forks);
		sim->forks = NULL;
	}
	if (sim->philos)
	{
		free(sim->philos);
		sim->philos = NULL;
	}
	if (sim->state)
	{
		free(sim->state);
		sim->state = NULL;
	}
	if (sim->print_lock)
	{
		free(sim->print_lock);
		sim->print_lock = NULL;
	}
	free_structures(sim, mutex_info);
	return ;
}
