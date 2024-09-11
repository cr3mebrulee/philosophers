/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_and_mutexes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:06 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/26 21:22:49 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutexes(t_simulation *sim)
{
	int	i;
	int	num;
	// const bool print_lock;
	// const bool state_lock;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_mutex_init(&(sim->forks[i]), NULL) != 0)
		{
			destroy_mutexes(sim, i, false, false);
			return (1);
		}
		if (pthread_mutex_init(&(sim->philos[i].time_lock), NULL) != 0)
		{
			destroy_mutexes(sim, i, false, false);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(sim->print_lock, NULL) != 0)
	{
		destroy_mutexes(sim, i, true, false);
		return (1);
	}
	if (pthread_mutex_init(sim->state, NULL) != 0)
	{
		destroy_mutexes(sim, i, true, true);
		return (1);
	}
	return (0);
}

int	init_philos(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	sim->if_alive = ALIVE;
	sim->satisfaction = STARVING;
	while (i < num)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].on_fork = 0;
		if (sim->philos[i].id == sim->number_of_philos)
		{
			sim->philos[i].right_fork = &sim->forks[(i + 1) % num];
			sim->philos[i].left_fork = &sim->forks[i];
		}
		else
		{
			sim->philos[i].right_fork = &sim->forks[i];
			sim->philos[i].left_fork = &sim->forks[(i + 1) % num];
		}
		sim->philos[i].sim = sim;
		sim->philos[i].last_meal_time = current_time();
		i++;
	}
	return (0);
}