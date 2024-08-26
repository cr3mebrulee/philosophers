/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_and_mutexes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:06 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/23 18:21:29 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_mutexes(t_simulation *sim)
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
	if (pthread_mutex_init(sim->print_lock, NULL) != 0)
	{
		return (1);
	}
	if (pthread_mutex_init(sim->state, NULL) != 0)
	{
		return(1);
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
		//assign left and right forks to philosophers with opposite order for the last philosopher
		if(sim->philos[i].id == sim->number_of_philos)
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

int	allocate_memory(t_simulation *sim)
{
	// Allocate memory for forks
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number_of_philos);
	if (!sim->forks)
	{
		return (1); // Return 1 if allocation fails
	}
	memset(sim->forks, 0, sizeof(pthread_mutex_t) * sim->number_of_philos);

	// Allocate memory for philosophers
	sim->philos = malloc(sizeof(t_philosopher) * sim->number_of_philos);
	if (!sim->philos)
	{
		free(sim->forks); // Free previously allocated memory
		return (1);
	}
	memset(sim->philos, 0, sizeof(t_philosopher) * sim->number_of_philos);

	// Allocate memory for state mutex
	sim->state = malloc(sizeof(pthread_mutex_t));
	if (!sim->state)
	{
		free(sim->philos); // Free previously allocated memory
		free(sim->forks);
		return (1);
	}
	memset(sim->state, 0, sizeof(pthread_mutex_t));

	// Allocate memory for print_lock mutex
	sim->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!sim->print_lock)
	{
		free(sim->state); // Free previously allocated memory
		free(sim->philos);
		free(sim->forks);
		return (1);
	}
	memset(sim->print_lock, 0, sizeof(pthread_mutex_t));
	return (0); // Return 0 on success
}
