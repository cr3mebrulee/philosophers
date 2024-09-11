/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taretiuk <taretiuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:45:43 by taretiuk          #+#    #+#             */
/*   Updated: 2024/07/31 12:37:34 by taretiuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_arguments(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf(USAGE_MESSAGE);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			printf("Usage: Arguments are positive integers.\n");
			return (0);
		}
		i++;
	}
	return (1);
}
