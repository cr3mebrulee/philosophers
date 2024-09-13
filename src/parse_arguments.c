/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:45:43 by taretiuk          #+#    #+#             */
/*   Updated: 2024/09/13 13:58:18 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		return (1);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_simulation *sim,
									t_mutex_info *mutex_info)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf(USAGE_MESSAGE);
		free_structures(sim, mutex_info);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (is_number(argv[i]))
		{
			printf("Usage: Arguments are positive integers.\n");
			free_structures(sim, mutex_info);
			return (1);
		}
		i++;
	}
	return (0);
}
