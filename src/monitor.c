/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:24:10 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/14 13:30:57 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		print_message(philo, "died");
		pthread_mutex_unlock(sim->state);
		return (1);
	}
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
				return (NULL);
			i++;
		}
		if (sim->number_of_meals != 0)
		{
			if (meals_finished(sim))
				return (NULL);
		}
		precise_sleep(10);
	}
	return (NULL);
}
