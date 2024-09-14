/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destriy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:55:27 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 11:55:40 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_state(t_simulation *sim)
{
	pthread_mutex_destroy(sim->state);
	return ;
}

static void	destroy_print(t_simulation *sim)
{
	pthread_mutex_destroy(sim->print_lock);
	return ;
}

static void	destroy_times(t_simulation *sim, int num_times)
{
	int	i;

	i = 0;
	while (i < num_times)
	{
		pthread_mutex_destroy(&(sim->philos[i].time_lock));
		i++;
	}
	return ;
}

static void	destroy_forks(t_simulation *sim, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		pthread_mutex_destroy(&(sim->forks[i]));
		i++;
	}
	return ;
}

void	destroy_mutexes(t_simulation *sim, t_mutex_info *mutex_info)
{
	if (mutex_info->num_forks > 0)
	{
		destroy_forks(sim, mutex_info->num_forks);
	}
	if (mutex_info->num_times > 0)
	{
		destroy_times(sim, mutex_info->num_times);
	}
	if (mutex_info->print_lock_init)
	{
		destroy_print(sim);
	}
	if (mutex_info->state_lock_init)
	{
		destroy_state(sim);
	}
}
