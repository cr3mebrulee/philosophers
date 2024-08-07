/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:24:10 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/07 15:02:44 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitor(void *arg);

void	check_meal_counts(t_simulation *sim)
{
	int	i;
	int	all_philos_done;

	i = 0;
	all_philos_done = 1;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_lock(&sim->philos[i].meal_time_lock);
		if (sim->philos[i].meals_eaten < sim->number_of_meals)
		{
			all_philos_done = 0;
		}
		pthread_mutex_unlock(&sim->philos[i].meal_time_lock);
		i++;
	}
	if (all_philos_done)
	{
		free(sim->philos);
		free(sim->forks);
		exit (0);
	}
}

void	report_philosopher_death(t_simulation *sim, int id, long long time)
{
	if (pthread_mutex_lock(&sim->print_lock) != 0)
	{
		initiate_termination(sim, 1, 1, 1);
		exit(2);
	}
	printf("%lld %d died\n", time, id);
	if (pthread_mutex_unlock(&sim->print_lock) != 0)
	{
		initiate_termination(sim, 1, 1, 1);
		exit(3);
	}
	initiate_termination(sim, 1, 1, 1);
	exit(3);
}

void	check_philosopher(t_simulation *sim, int i)
{
	long long	current_time;

	if (pthread_mutex_lock(&sim->philos[i].meal_time_lock) != 0)
	{
		initiate_termination(sim, 1, 1, 1);
		exit (1);
	}
	current_time = current_timestamp() - sim->philos[i].last_meal_time;
	if (current_time > sim->time_to_die)
	{
		pthread_mutex_unlock(&sim->philos[i].meal_time_lock);
		report_philosopher_death(sim, sim->philos[i].id, current_time);
	}
	if (pthread_mutex_unlock(&sim->philos[i].meal_time_lock) != 0)
	{
		initiate_termination(sim, 1, 1, 1);
		exit (4);
	}
}

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->number_of_philos)
		{
			check_philosopher(sim, i);
			i++;
		}
		check_meal_counts(sim);
		usleep(1000);
	}
	return (NULL);
}
