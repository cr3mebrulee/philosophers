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

static char take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->sim->print_lock);
    printf("%lld %d has taken a right fork\n", current_time(), philo->id);
	printf("%lld %d has taken a left fork\n", current_time(), philo->id);
	printf("%lld %d is eating\n", current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
    return (0);
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time_lock);
	philo->meals_eaten++;
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->time_lock);
	precise_sleep(philo->sim->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return ;
}

// Simulate the philosopher sleeping
void	sleep_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%lld %d is sleeping\n", current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
	usleep(philo->sim->time_to_sleep * 1000);
	return ;
}

// Simulate the philosopher thinking
void	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%lld %d is thinking\n", current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

// Philosopher routine
void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		take_forks(philo);
		eat(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}
