/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers_and_forks.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:06 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 13:47:56 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	initialize_mutexes(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_mutex_init(&(sim->forks[i]), NULL) != 0)
		{
			return (1);
		}
		if (pthread_mutex_init(&(sim->philos[i].time_lock), NULL) != 0)
		{
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
	{
		return (1);
	}
	return (0);
}

int	initialize_philosophers(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	//sim->stop_simulation = 0;
	while (i < num)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].if_alive = ALIVE;
		if (sim->philos[i].id % 2 == 0)
		{
			sim->philos[i].left_fork = &sim->forks[i];
			sim->philos[i].right_fork = &sim->forks[(i + 1) % num];
		}
		else
		{
			sim->philos[i].left_fork = &sim->forks[(i + 1) % num];
			sim->philos[i].right_fork = &sim->forks[i];
		}
		sim->philos[i].simulation = sim;
		sim->philos[i].meal_time = current_timestamp();
		i++;
	}
	return (0);
}

int	initialize_philosophers_and_forks(t_simulation *sim)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number_of_philos);
	if (!sim->forks)
	{
		return (1);
	}
	sim->philos = malloc(sizeof(t_philosopher) * sim->number_of_philos);
	memset(sim->philos, 0, sizeof(t_simulation) * sim->number_of_philos);
	if (!sim->philos)
	{
		return (1);
	}
	sim->thread = malloc(sizeof(pthread_t) * sim->number_of_philos);
	if (!sim->thread)
	{
		return (1);
	}
	memset(sim->thread, 0, sizeof(pthread_t) * sim->number_of_philos);
	if (initialize_mutexes(sim) != 0)
	{
		free_resources(sim);
		return (1);
	}
	if (initialize_philosophers(sim) != 0)
	{
		destroy_forks(sim);
		free_resources(sim);
		return (1);
	}
	return (0);
}
