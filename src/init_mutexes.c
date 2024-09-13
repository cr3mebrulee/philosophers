/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:21:57 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 11:04:51 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex_state(t_simulation *sim)
{
	int	num;

	num = sim->number_of_philos;
	if (pthread_mutex_init(sim->state, NULL) != 0)
	{
		destroy_mutexes(sim, num, num, true, false);
		free_memory(sim);
		return (1);
	}
}

static int	init_mutex_print(t_simulation *sim)
{
	int	num;

	num = sim->number_of_philos;
	if (pthread_mutex_init(sim->print_lock, NULL) != 0)
	{
		destroy_mutexes(sim, num, num, false, false);
		free_memory(sim);
		return (1);
	}
}

static int	init_mutexes_time(t_simulation *sim)
{
	int	i;
	int	num;
	int	num_time;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_mutex_init(&(sim->philos[i].time_lock), NULL) != 0)
		{
			destroy_mutexes(sim, num, i, false, false);
			free_memory(sim);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mutexes_forks(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_mutex_init(&(sim->forks[i]), NULL) != 0)
		{
			destroy_mutexes(sim, i, 0, false, false);
			free_memory(sim);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutexes(t_simulation *sim)
{
	if (init_mutexes_forks(sim) != 0)
	{
		return (1);
	}
	if (init_mutexes_time(sim) != 0)
	{
		return (1);
	}
	if (init_mutex_print(sim) != 0)
	{
		return (1);
	}
	if (init_mutex_state(sim) != 0)
	{
		return (1);
	}
	return (0);
}

