/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:34:18 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/14 12:07:24 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void destroy_mutexes(t_simulation *sim, int num_init_mutex, const bool print_lock, const bool state_lock)
{
    int i;

    i = 0;
    while (i < num_init_mutex)
    {
        pthread_mutex_destroy(&(sim->forks[i]));
        pthread_mutex_destroy(&(sim->philos[i].time_lock));
        i++;
    }
    if (print_lock == true)
    {
        pthread_mutex_destroy(sim->print_lock);
    }
    if (state_lock == true)
    {
        pthread_mutex_destroy(sim->state);
    }
}

void free_memory(t_simulation *sim)
{
    if (sim->forks)
    {
        free(sim->forks);
        sim->forks = NULL;
    }
    if (sim->philos)
    {
        free(sim->philos);
        sim->philos = NULL;
    }
    if (sim->state)
    {
        free(sim->state);
        sim->state = NULL;
    }
    if (sim->print_lock)
    {
        free(sim->print_lock);
        sim->print_lock = NULL;
    }
    if (sim)
    {
        free(sim);
        sim = NULL;
    }
}