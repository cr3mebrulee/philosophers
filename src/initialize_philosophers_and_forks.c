/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers_and_forks.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:06 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/07 16:35:52 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	initialize_philosophers(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal_time = current_timestamp();
		sim->philos[i].left_fork = &sim->forks[i];
		sim->philos[i].right_fork = &sim->forks[(i + 1) % num];
		sim->philos[i].simulation = sim;
		if (pthread_mutex_init(&sim->philos[i].meal_time_lock, NULL) != 0)
		{
			printf("Error: Failed to initialize meal time mutex.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	initialize_forks(t_simulation *sim)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			printf("Error: Failed to initialize forks mutex.\n");
			return (1);
		}
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
	if (!sim->philos)
	{
		return (1);
	}
	if (initialize_forks(sim) != 0)
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
