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

#include "../include/philosophers.h"

int free_resources(t_simulation *sim, int forks, int philos)
{
    if (forks == 1 && sim->forks != NULL)
    {
        free(sim->forks);
        sim->forks = NULL;
    }
    if (philos == 1 && sim->philos != NULL)
    {
        free(sim->philos);
        sim->philos = NULL;
    }
    return (0);
}