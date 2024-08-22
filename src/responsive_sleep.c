/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responsive_sleep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:49:52 by taretiuk          #+#    #+#             */
/*   Updated: 2024/08/12 17:50:09 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	precise_sleep(unsigned long duration, t_simulation *sim)
{
	unsigned long	start;

	start = current_timestamp();
	while (!sim->stop_simulation)
	{
		if (current_timestamp() - start >= duration)
			break ;
		usleep(sim->number_of_philos * 2);
	}
	return ;
}
