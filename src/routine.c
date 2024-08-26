/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:10:09 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/26 20:53:55 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static char	take_forks(t_philosopher *philo)
{
    // Attempt to lock the state mutex
    if (pthread_mutex_trylock(philo->sim->state) != 0) {
        printf("Philosopher %d: Failed to lock state mutex in take_forks\n", philo->id);
        return (1); // Early return for debugging purposes
    }
    philo->on_fork = 0;
    if (philo->sim->if_alive == DEAD)
    {
        pthread_mutex_unlock(philo->sim->state);
        return (1);
    }

    // Attempt to lock the right fork mutex
    if (pthread_mutex_trylock(philo->right_fork) != 0) {
        printf("Philosopher %d: Failed to lock right fork\n", philo->id);
        pthread_mutex_unlock(philo->sim->state);
        return (1); // Early return for debugging purposes
    }
    philo->on_fork = 1;

    if (philo->right_fork == philo->left_fork)
    {
        pthread_mutex_unlock(philo->sim->state);
        printf("%lld %d has taken a fork\n", current_time(), philo->id);
        return (1);
    }

    pthread_mutex_unlock(philo->sim->state);

    // Attempt to lock the left fork mutex
    if (pthread_mutex_trylock(philo->left_fork) != 0) {
        printf("Philosopher %d: Failed to lock left fork\n", philo->id);
        pthread_mutex_unlock(philo->right_fork);
        return (1); // Early return for debugging purposes
    }

    pthread_mutex_lock(philo->sim->print_lock);
    philo->on_fork = 2;
    printf("%lld %d has taken a fork\n", current_time(), philo->id);
    printf("%lld %d has taken a fork\n", current_time(), philo->id);
    pthread_mutex_unlock(philo->sim->print_lock);
    return (0);
}

static char	eat(t_philosopher *philo)
{
    // Attempt to lock the state mutex
    if (pthread_mutex_trylock(philo->sim->state) != 0) {
        printf("Philosopher %d: Failed to lock state mutex in eat\n", philo->id);
        return (1); // Early return for debugging purposes
    }

    if(philo->sim->if_alive == DEAD)
    {
        pthread_mutex_unlock(philo->sim->state);
        return (1);
    }
    pthread_mutex_unlock(philo->sim->state);

    // Attempt to lock the time_lock mutex
    if (pthread_mutex_trylock(&philo->time_lock) != 0) {
        printf("Philosopher %d: Failed to lock time mutex in eat\n", philo->id);
        return (1); // Early return for debugging purposes
    }
    philo->last_meal_time = current_time();
    pthread_mutex_unlock(&philo->time_lock);

    pthread_mutex_lock(philo->sim->print_lock);
    printf("%lld %d is eating\n", philo->last_meal_time, philo->id);
    pthread_mutex_unlock(philo->sim->print_lock);

    precise_sleep(philo->sim->time_to_eat);

    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);

    return (0);
}

// Simulate the philosopher sleeping
static char	sleep_philo(t_philosopher *philo)
{
    pthread_mutex_lock(philo->sim->print_lock);
    printf("%lld %d is sleeping\n", current_time(), philo->id);
    pthread_mutex_unlock(philo->sim->print_lock);

    precise_sleep(philo->sim->time_to_sleep);

    // Attempt to lock the state mutex
    if (pthread_mutex_trylock(philo->sim->state) != 0) {
        printf("Philosopher %d: Failed to lock state mutex in sleep_philo\n", philo->id);
        return (1); // Early return for debugging purposes
    }

    philo->meals_eaten++;
    philo->on_fork = 0;

    if (philo->sim->if_alive == DEAD)
    {
        pthread_mutex_unlock(philo->sim->state);
        return (1);
    }

    if (philo->sim->satisfaction == SATISFIED)
    {
        pthread_mutex_unlock(philo->sim->state);
        return (1);
    }

    pthread_mutex_unlock(philo->sim->state);
    return (0);
}

// Simulate the philosopher thinking
static char	think(t_philosopher *philo)
{
    pthread_mutex_lock(philo->sim->print_lock);
    printf("%lld %d is thinking\n", current_time(), philo->id);
    pthread_mutex_unlock(philo->sim->print_lock);
	usleep(rand() % 2000);
    // Attempt to lock the state mutex
    if (pthread_mutex_trylock(philo->sim->state) != 0) {
        printf("Philosopher %d: Failed to lock state mutex in think\n", philo->id);
        return (1); // Early return for debugging purposes
    }
    if(philo->sim->if_alive == DEAD)
    {
        pthread_mutex_unlock(philo->sim->state);
        return (1);
    }

    pthread_mutex_unlock(philo->sim->state);
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
	if (philo->on_fork == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
	}
	if (philo->on_fork == 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (NULL);
}
