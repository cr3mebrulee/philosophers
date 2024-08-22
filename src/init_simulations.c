/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_simulations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:11:18 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 15:57:58 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_simulations(int argc, char **argv, t_simulation *sim)
{
	sim->number_of_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		sim->number_of_meals = ft_atoi(argv[5]);
	}
	else
	{
		sim->number_of_meals = 0;
	}
	if (sim->number_of_philos <= 0 || sim->time_to_die <= 0
		|| sim->time_to_eat <= 0 || sim->time_to_sleep <= 0
		|| (argc == 6 && sim->number_of_meals < 0))
	{
		ft_printf("Usage: Arguments are positive integers greater than zero.\n");
		return (1);
	}
	return (0);
}
