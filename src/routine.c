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
	if (philo->right_fork == philo->left_fork)
	{
		printf("%lld %d has taken a fork\n", current_time(), philo->id);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->sim->print_lock);
    printf("%lld %d has taken a fork\n", current_time(), philo->id);
	printf("%lld %d has taken a fork\n", current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
    return (0);
}

static char	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->time_lock);
	if(philo->if_alive == DEAD)
	{
		printf("Philosopher %d is DEAD\n", philo->id);
		return (1);
	}
	philo->last_meal_time = current_time();
	philo->meals_eaten++;
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%lld %d is eating\n", current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
	pthread_mutex_unlock(&philo->time_lock);
	precise_sleep(philo->sim->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("\033[1;31mPhilo %d ate %d times\033[0m\n", philo->id, philo->meals_eaten);
	pthread_mutex_unlock(&philo->sim->print_lock);	
	return (0);
}

// Simulate the philosopher sleeping
static char	sleep_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%lld %d is sleeping\n", current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
	precise_sleep(philo->sim->time_to_sleep);
	return (0);
}

// Simulate the philosopher thinking
static char	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	printf("%lld %d is thinking\n", current_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->print_lock);
	return (0);
}

// Philosopher routine
void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
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
	return (NULL);
}
