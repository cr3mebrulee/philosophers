/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:34:18 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 11:16:35 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_state(t_simulation *sim)
{
	pthread_mutex_destroy(sim->state);
	return ;
}

static void	destroy_print(t_simulation *sim)
{
	pthread_mutex_destroy(sim->print_lock);
	return ;
}

static void	destroy_times(t_simulation *sim, int num_times)
{
	int	i;

	i = 0;
	while (i < num_times)
	{
		pthread_mutex_destroy(&(sim->philos[i].time_lock));
		i++;
	}
	return ;
}

static void	destroy_forks(t_simulation *sim, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		pthread_mutex_destroy(&(sim->forks[i]));
		i++;
	}
	return ;
}

void	destroy_mutexes(t_simulation *sim, int num_forks, int num_times,
				const bool print_lock, const bool state_lock)
{
	if (num_forks > 0)
	{
		destroy_forks(sim, num_forks);
	}
	if (num_times > 0)
	{
		destroy_times(sim, num_times);
	}
	if (print_lock == true)
	{
		destroy_print(sim);
	}
	if (state_lock == true)
	{
		destroy_state(sim);
	}
}

void	free_memory(t_simulation *sim)
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
	if (sim)
	{
		free(sim);
		sim = NULL;
	}
}
