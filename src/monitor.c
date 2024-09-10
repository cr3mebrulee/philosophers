/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:24:10 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/26 21:23:17 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	meals_finished(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(sim->state);
	while (i < sim->number_of_philos)
	{
		if (sim->philos[i].meals_eaten < sim->number_of_meals)
		{
			pthread_mutex_unlock(sim->state);
			return (0);
		}
		i++;
	}
	sim->satisfaction = SATISFIED;
	pthread_mutex_unlock(sim->state);
	return (1);
}

int	if_alive(t_philosopher *philo, t_simulation *sim)
{

	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->time_lock);
	time_since_last_meal = current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->time_lock);
	if (time_since_last_meal > sim->time_to_die)
	{
		pthread_mutex_lock(sim->state);
		sim->if_alive = DEAD;
		pthread_mutex_lock(sim->print_lock);
		printf("\033[1;31m%lld %d died after %lld\033[0m\n", current_time(), philo->id, time_since_last_meal);
		pthread_mutex_unlock(sim->print_lock);
		pthread_mutex_unlock(sim->state);
		return (1);
	}
	pthread_mutex_unlock(sim->state);
	return (0);
}

void	*monitor(void *arg)
{
	int				i;
	t_simulation	*sim;

	i = 0;
	sim = (t_simulation *)arg;
	while (1)
	{
		i = 0;
		while (i < sim->number_of_philos)
		{
			if (if_alive(&sim->philos[i], sim))
			{
				return (NULL);
			}
			i++;
		}
		if (sim->number_of_meals != 0)
		{
			if (meals_finished(sim))
			{
				return (NULL);
			}
		}
 		precise_sleep (100);
	}
	return (NULL);
}
