/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:55:56 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/23 19:34:52 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	precise_sleep(int ms)
{
	struct timeval	start;
	struct timeval	end;
	long long		elapsed_time;

	elapsed_time = 0;
	gettimeofday(&start, NULL);
	while (elapsed_time < ms)
	{
		usleep(10);
		gettimeofday(&end, NULL);
		elapsed_time = (end.tv_sec - start.tv_sec) * 1000LL
			+ (end.tv_usec - start.tv_usec) / 1000;
	}
}
