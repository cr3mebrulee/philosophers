/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:24:10 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/24 17:51:32 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	if_alive(t_philosopher *philo, t_simulation *sim)
{
	int	i;
	long long	time_since_last_meal;

	i = 0;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_lock(&philo->time_lock);
		time_since_last_meal = current_time() - philo->last_meal_time;
		if (time_since_last_meal > sim->time_to_die)
		{
			//block
			philo->if_alive = DEAD;
			pthread_mutex_unlock(&philo->time_lock);
			//block
			pthread_mutex_lock(&sim->print_lock);
			printf("\033[1;31m%lld %d died\033[0m\n", time_since_last_meal, philo->id);
			pthread_mutex_unlock(&sim->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->time_lock);
		i++;
	}
	return (0);
}

void *monitor(void *arg)
{
	int				i;
	t_simulation	*sim;

	i = 0;
	sim = (t_simulation *)arg;
	while (1)
	{
		if (if_alive(&sim->philos[i], sim))
		{
			exit (0);
		}
	}
	return (NULL);
}
