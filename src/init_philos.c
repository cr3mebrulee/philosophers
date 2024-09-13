/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:15:06 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 10:22:38 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assignments(t_simulation *sim, int i, int num)
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
		assignments(sim, i, num);
		i++;
	}
	return (0);
}
