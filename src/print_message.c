/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:30:29 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:25 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_message(t_philosopher *philo, const char *message)
{
	pthread_mutex_lock(philo->sim->print_lock);
	printf("%lld %d %s\n", current_time(), philo->id, message);
	pthread_mutex_unlock(philo->sim->print_lock);
}
