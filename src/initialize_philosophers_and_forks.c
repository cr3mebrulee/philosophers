/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers_and_forks.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:06 by taretiuk          #+#    #+#             */
/*   Updated: 2024/07/29 16:15:13 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	initialize_philosophers(t_simulation *sim)
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
		if (pthread_mutex_init(&sim->philos[i].meal_time_lock, NULL) != 0) // Initialize meal_time_lock
		{
			ft_printf("Error: Failed to initialize meal time mutex for philosopher %d.\n", i + 1);
			return ;
		}
		i++;
	}
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
			ft_printf("Error: Failed to initialize mutex.\n");
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
		free(sim->forks);
		return (1);
	}
	if (initialize_forks(sim) != 0)
	{
		free(sim->philos);
		free(sim->forks);
		return (1);
	}
	initialize_philosophers(sim);
	return (0);
}
