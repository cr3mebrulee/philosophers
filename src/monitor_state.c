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

/*check*/

int	report_philosopher_death(t_simulation *sim, int id, long long time)
{
	pthread_mutex_lock(&sim->print_lock);
	printf("%lld %d died\n", time, id);
	pthread_mutex_unlock(&sim->print_lock);
	return (0);
}

int	check_meal_counts(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_philos)
	{
		pthread_mutex_lock(&sim->philos[i].time_lock);
		if (sim->philos[i].meals_eaten < sim->number_of_meals)
		{
			sim->philos[i].status = SATISFIED;
			return (0);
		}
		pthread_mutex_unlock(&sim->philos[i].time_lock);
		i++;
	}
	// if (all_philos_done)
	// {
	// 	free(sim->philos);
	// 	free(sim->forks);
	// 	return (1);
	// }
	return (0);
}

int	if_alive(t_philosopher *philo, t_simulation *sim, char *active, int i)
{
	long long	current_time;

	pthread_mutex_lock(&philo->time_lock);
	current_time = current_timestamp() - philo->last_meal_time;
	if (current_time > sim->time_to_die)
	{
		philo->if_alive = DEAD;
		pthread_mutex_lock(&sim->print_lock);
		printf("%lld %d died\n", time, &sim->philos[i].id);
		pthread_mutex_unlock(&sim->print_lock);
		pthread_mutex_unlock(&philo->time_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->time_lock);
	return (0);
}

void *monitor_state(void *arg)
{
	t_simulation *sim = (t_simulation *)arg;
	int	i;
	int active = 0;

	while (1)
	{
		i = 0;
		active = 0;
		while (i < sim->number_of_philos)
		{
			if (!if_alive(&sim->philos[i], sim, &active, i))
			{
				active = 0;
				break ;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
