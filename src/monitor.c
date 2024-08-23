/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:24:10 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 17:42:00 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_meal_counts(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_lock(&sim->philos[i].time_lock);
		if (sim->philos[i].meals_eaten < sim->number_of_meals)
		{
			pthread_mutex_unlock(&sim->philos[i].time_lock);
			return (0); // Not all philosophers are satisfied yet
		}
		pthread_mutex_unlock(&sim->philos[i].time_lock);
		i++;
	}
	// All philosophers have eaten the required number of meals
	// You can add any necessary cleanup here or handle it elsewhere.
	return (1);
}

int	if_alive(t_philosopher *philo, t_simulation *sim)
{
	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->time_lock);
	time_since_last_meal = current_time() - philo->last_meal_time;
	if (time_since_last_meal > sim->time_to_die)
	{
		philo->if_alive = DEAD;
		pthread_mutex_unlock(&philo->time_lock);
		pthread_mutex_lock(&sim->print_lock);
		printf("\033[1;31m%lld %d died\033[0m\n", time_since_last_meal, philo->id);
		pthread_mutex_unlock(&sim->print_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->time_lock);
	return (1); // Return 1 to indicate the philosopher is still alive
}

void *monitor(void *arg)
{
	t_simulation *sim = (t_simulation *)arg;
	int	i;

	while (1)
	{
		i = 0;
		while (i < sim->number_of_philos)
		{
			if (!if_alive(&sim->philos[i], sim))
			{
				return (NULL);
			}
			i++;
		}
		if (check_meal_counts(sim))
		{
			return (NULL);
		}
		usleep(1000); // Sleep for a short time to avoid busy waiting
	}
	return (NULL);
}