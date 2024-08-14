/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:10:09 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 12:07:38 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// Get the current timestamp in milliseconds
long long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

// Simulate the philosopher eating
void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->simulation->print_lock);
	printf("%lld %d is eating\n", current_timestamp(), philo->id);
	pthread_mutex_unlock(&philo->simulation->print_lock);
	pthread_mutex_lock(&philo->time_lock);
	philo->last_meal_time = current_timestamp();
	pthread_mutex_unlock(&philo->time_lock);
	usleep(philo->simulation->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}

// Simulate the philosopher sleeping
void	sleep_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->simulation->print_lock);
	printf("%lld %d is sleeping\n", current_timestamp(), philo->id);
	pthread_mutex_unlock(&philo->simulation->print_lock);
	usleep(philo->simulation->time_to_sleep * 1000);
	return ;
}

// Simulate the philosopher thinking
void	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->simulation->print_lock);
	printf("%lld %d is thinking\n", current_timestamp(), philo->id);
	pthread_mutex_unlock(&philo->simulation->print_lock);
}

// Philosopher routine
void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	sim = NULL;
	philo = (t_philosopher *)arg;
	while (1)
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}
