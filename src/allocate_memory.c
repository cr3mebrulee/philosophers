/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:55:42 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:58 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	allocate_philos(t_simulation *sim, t_mutex_info *mutex_info)
{
	sim->philos = malloc(sizeof(t_philosopher) * sim->number_of_philos);
	if (!sim->philos)
	{
		free_memory(sim, mutex_info);
		return (1);
	}
	memset(sim->philos, 0, sizeof(t_philosopher) * sim->number_of_philos);
	return (0);
}

int	allocate_mutexes(t_simulation *sim, t_mutex_info *mutex_info)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number_of_philos);
	if (!sim->forks)
	{
		free_structures(sim, mutex_info);
		return (1);
	}
	memset(sim->forks, 0, sizeof(pthread_mutex_t) * sim->number_of_philos);
	sim->state = malloc(sizeof(pthread_mutex_t));
	if (!sim->state)
	{
		free_memory(sim, mutex_info);
		return (1);
	}
	memset(sim->state, 0, sizeof(pthread_mutex_t));
	sim->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!sim->print_lock)
	{
		free_memory(sim, mutex_info);
		return (1);
	}
	memset(sim->print_lock, 0, sizeof(pthread_mutex_t));
	return (0);
}

int	allocate_memory(t_simulation *sim, t_mutex_info *mutex_info)
{
	if (allocate_philos(sim, mutex_info) != 0)
	{
		return (1);
	}
	if (allocate_mutexes(sim, mutex_info) != 0)
	{
		return (1);
	}
	return (0);
}
