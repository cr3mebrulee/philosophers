/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:10:09 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:16 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static char	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->sim->state);
	philo->on_fork = 0;
	if (philo->sim->if_alive == DEAD)
	{
		return (1);
	}
	philo->on_fork = 1;
	pthread_mutex_unlock(philo->sim->state);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->sim->state);
	if (philo->right_fork == philo->left_fork)
	{
		print_message(philo, "has taken a fork");
		return (1);
	}
	if (philo->sim->if_alive == DEAD)
	{
		return (1);
	}
	print_message(philo, "has taken a fork");
	pthread_mutex_unlock(philo->sim->state);
	pthread_mutex_lock(philo->left_fork);
	return (0);
}

static char	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->time_lock);
	pthread_mutex_lock(philo->sim->state);
	philo->on_fork = 2;
	if (philo->sim->if_alive == DEAD)
	{
		return (1);
	}
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_unlock(philo->sim->state);
	precise_sleep(philo->sim->time_to_eat);
	return (0);
}

static char	sleep_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->sim->state);
	if (philo->sim->if_alive == DEAD)
	{
		return (1);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->on_fork = 0;
	philo->meals_eaten++;
	print_message(philo, "is sleeping");
	pthread_mutex_unlock(philo->sim->state);
	precise_sleep(philo->sim->time_to_sleep);
	return (0);
}

static char	think(t_philosopher *philo)
{
	pthread_mutex_lock(philo->sim->state);
	if (philo->sim->if_alive == DEAD)
	{
		return (1);
	}
	if (philo->sim->satisfaction == SATISFIED)
	{
		return (1);
	}
	print_message(philo, "is thinking");
	pthread_mutex_unlock(philo->sim->state);
	return (0);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
	{
		precise_sleep(philo->sim->time_to_eat / 2);
	}
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->time_lock);
	while (1)
	{
		if (take_forks(philo)
			|| eat(philo)
			|| sleep_philo(philo)
			|| think(philo))
			break ;
	}
	release_mutexes(philo);
	return (NULL);
}
