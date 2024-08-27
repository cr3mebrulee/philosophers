/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:10:09 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/27 17:19:48 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// if (philo->right_fork == philo->left_fork)
// 	{
// 		pthread_mutex_unlock(philo->sim->state);
// 		printf("%lld %d has taken a fork\n", current_time(), philo->id);
// 		return (1);
// 	}

static char	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->sim->state);
	if (philo->sim->if_alive == DEAD)
	{
		pthread_mutex_unlock(philo->sim->state);
		return (1);
	}
	pthread_mutex_unlock(philo->sim->state);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->sim->state);
	if (philo->sim->if_alive == DEAD)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->sim->state);
		return (1);
	}
	pthread_mutex_lock(philo->sim->print_lock);
	printf("%lld %d has taken a fork\n", current_time(), philo->id);
	pthread_mutex_unlock(philo->sim->print_lock);
	pthread_mutex_unlock(philo->sim->state);
	pthread_mutex_lock(philo->left_fork);
	return (0);
}

static char	eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->sim->state);
	if(philo->sim->if_alive == DEAD)
	{
		pthread_mutex_unlock(philo->sim->state);
		return (1);
	}
	pthread_mutex_lock(philo->sim->print_lock);
	printf("%lld %d has taken a fork\n", current_time(), philo->id);
	printf("%lld %d is eating\n", philo->last_meal_time, philo->id);
	pthread_mutex_unlock(philo->sim->print_lock);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(philo->sim->state);
	precise_sleep(philo->sim->time_to_eat);
	return (0);
}

// Simulate the philosopher sleeping
static char	sleep_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->sim->state);
	if(philo->sim->if_alive == DEAD)
	{
		pthread_mutex_unlock(philo->sim->state);
		return (1);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->meals_eaten++;
	pthread_mutex_lock(philo->sim->print_lock);
	printf("%lld %d is sleeping\n", current_time(), philo->id);
	pthread_mutex_unlock(philo->sim->print_lock);
	pthread_mutex_unlock(philo->sim->state);
	precise_sleep(philo->sim->time_to_sleep);
	// if (philo->sim->if_alive == DEAD)
	// {
	// 	pthread_mutex_unlock(philo->sim->state);
	// 	return (1);
	// }
	// pthread_mutex_unlock(philo->sim->state);
	return (0);
}

// Simulate the philosopher thinking
static char	think(t_philosopher *philo)
{
	pthread_mutex_lock(philo->sim->state);
	if(philo->sim->if_alive == DEAD)
	{
		pthread_mutex_unlock(philo->sim->state);
		return (1);
	}
	if (philo->sim->satisfaction == SATISFIED)
	{
		pthread_mutex_unlock(philo->sim->state);
		return (1);
	}
	pthread_mutex_lock(philo->sim->print_lock);
	printf("%lld %d is thinking\n", current_time(), philo->id);
	pthread_mutex_unlock(philo->sim->print_lock);
	pthread_mutex_unlock(philo->sim->state);
	return (0);
}

// Philosopher routine
void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(philo->sim->state);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(philo->sim->state);
	while (1)
	{
		if (take_forks(philo)
				|| eat(philo)
				|| sleep_philo(philo)
				|| think(philo))
				break ;
	}
	// if (philo->on_fork == 1)
	// {
	// 	pthread_mutex_unlock(philo->right_fork);
	// }
	// if (philo->on_fork == 2)
	// {
	// 	pthread_mutex_unlock(philo->right_fork);
	// 	pthread_mutex_unlock(philo->left_fork);
	// }
	return (NULL);
}
