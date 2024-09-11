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

#include "philosophers.h"

void	print_simulation(t_simulation *sim)
{
	printf("Simulation Parameters:\n");
	printf("Number of Philosophers: %d\n", sim->number_of_philos);
	printf("Time to Die: %d\n", sim->time_to_die);
	printf("Time to Eat: %d\n", sim->time_to_eat);
	printf("Time to Sleep: %d\n", sim->time_to_sleep);
	printf("Number of Meals: %d\n\n", sim->number_of_meals);
}
