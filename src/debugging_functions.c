/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:08:39 by taretiuk          #+#    #+#             */
/*   Updated: 2024/07/29 16:19:46 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_philosopher_info(t_simulation *sim, int num)
{
	int	i;
	//t_philosopher *philos;

	for (i = 0; i < num; i++)
	{
		printf("Philosopher %d:\n", sim->philos[i].id);
		printf("ID of philosopher: %d\n", sim->philos[i].id);
		printf("Meals eaten: %d\n", sim->philos[i].meals_eaten);
		printf("Last meal time: %lld\n", sim->philos[i].last_meal_time);
		printf("Left fork: %p\n", (void *)sim->philos[i].left_fork);
		printf("Right fork: %p\n", (void *)sim->philos[i].right_fork);
		printf("Simulation: %p\n", (void *)sim->philos[i].sim);
		printf("\n");
	}
}

void	print_simulation(t_simulation *sim)
{
	printf("Simulation Parameters:\n");
	printf("Number of Philosophers: %d\n", sim->number_of_philos);
	printf("Time to Die: %d\n", sim->time_to_die);
	printf("Time to Eat: %d\n", sim->time_to_eat);
	printf("Time to Sleep: %d\n", sim->time_to_sleep);
	printf("Number of Meals: %d\n\n", sim->number_of_meals);
}
