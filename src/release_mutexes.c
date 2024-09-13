/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:31:21 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/12 18:32:15 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_mutexes(t_philosopher *philo)
{
	if (philo->on_fork == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
	}
	if (philo->on_fork == 2)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	pthread_mutex_unlock(philo->sim->state);
}
