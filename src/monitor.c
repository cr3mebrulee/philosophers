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

int meals_finished(t_simulation *sim)
{
    int i;

    //pthread_mutex_lock(sim->state);
    for (i = 0; i < sim->number_of_philos; i++)
    {
        if (sim->philos[i].meals_eaten < sim->number_of_meals)
        {
           // pthread_mutex_unlock(sim->state);
            return (0);  // Not all philosophers have finished eating
        }
    }
  // pthread_mutex_unlock(sim->state);
    return (1);  // All philosophers have finished eating
}

int if_alive(t_philosopher *philo, t_simulation *sim)
{
    int i;
    long long time_since_last_meal;

    i = 0;
    pthread_mutex_lock(&philo->time_lock);
    time_since_last_meal = current_time() - philo->last_meal_time;
    if (time_since_last_meal > sim->time_to_die)
    {
        pthread_mutex_lock(sim->state);
        while(i < sim->number_of_philos)
        {
            sim->philos[i].if_alive = DEAD;
            i++;
        }
        pthread_mutex_unlock(sim->state);
        pthread_mutex_unlock(&philo->time_lock);
        pthread_mutex_lock(sim->print_lock);
        printf("\033[1;31m%lld %d died\033[0m\n", current_time(), philo->id);
        pthread_mutex_unlock(sim->print_lock);
        return (1);
    }
    pthread_mutex_unlock(&philo->time_lock);
    return (0);
}

void *monitor(void *arg)
{
	int			i;
    t_simulation *sim;

	i = 0;
	sim = (t_simulation *)arg;
    while (1)
    {
		i = 0;
        while (i < sim->number_of_philos)
        {
            if (if_alive(&sim->philos[i], sim))
            {
                return (NULL);  // Exit if a philosopher has died
            }
			i++;
        }
        if (sim->number_of_meals != 0)
		{
			if(meals_finished(sim))
        	{
        	    exit(0);  // Exit if all philosophers have finished eating
        	}
		}
 		precise_sleep(100); //Small delay to prevent high CPU usage
    }
    return NULL;
}
