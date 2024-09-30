/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:21:57 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:43 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	init_mutex_state(t_simulation *sim, t_mutex_info *mutex_info)
{
	if (pthread_mutex_init(sim->state, NULL) != 0)
	{
		mutex_info->state_lock_init = false;
		destroy_mutexes(sim, mutex_info);
		free_memory(sim, mutex_info);
		return (1);
	}
	mutex_info->state_lock_init = true;
	return (0);
}

static int	init_mutex_print(t_simulation *sim, t_mutex_info *mutex_info)
{
	if (pthread_mutex_init(sim->print_lock, NULL) != 0)
	{
		mutex_info->print_lock_init = false;
		destroy_mutexes(sim, mutex_info);
		free_memory(sim, mutex_info);
		return (1);
	}
	mutex_info->print_lock_init = true;
	return (0);
}

static int	init_mutexes_time(t_simulation *sim, t_mutex_info *mutex_info)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_mutex_init(&(sim->philos[i].time_lock), NULL) != 0)
		{
			mutex_info->num_times = i;
			destroy_mutexes(sim, mutex_info);
			free_memory(sim, mutex_info);
			return (1);
		}
		i++;
	}
	mutex_info->num_times = num;
	return (0);
}

static int	init_mutexes_forks(t_simulation *sim, t_mutex_info *mutex_info)
{
	int	i;
	int	num;

	i = 0;
	num = sim->number_of_philos;
	while (i < num)
	{
		if (pthread_mutex_init(&(sim->forks[i]), NULL) != 0)
		{
			mutex_info->num_forks = i;
			destroy_mutexes(sim, mutex_info);
			free_memory(sim, mutex_info);
			return (1);
		}
		i++;
	}
	mutex_info->num_forks = num;
	return (0);
}

int	init_mutexes(t_simulation *sim, t_mutex_info *mutex_info)
{
	mutex_info->num_forks = 0;
	mutex_info->num_times = 0;
	mutex_info->print_lock_init = false;
	mutex_info->state_lock_init = false;
	if (init_mutexes_forks(sim, mutex_info) != 0)
	{
		return (1);
	}
	if (init_mutexes_time(sim, mutex_info) != 0)
	{
		return (1);
	}
	if (init_mutex_print(sim, mutex_info) != 0)
	{
		return (1);
	}
	if (init_mutex_state(sim, mutex_info) != 0)
	{
		return (1);
	}
	return (0);
}
