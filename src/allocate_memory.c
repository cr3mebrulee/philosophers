#include "philosophers.h"

int	allocate_memory(t_simulation *sim)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->number_of_philos);
	if (!sim->forks)
	{
		return (1);
	}
	memset(sim->forks, 0, sizeof(pthread_mutex_t) * sim->number_of_philos);
	sim->philos = malloc(sizeof(t_philosopher) * sim->number_of_philos);
	if (!sim->philos)
	{
		return (1);
	}
	memset(sim->philos, 0, sizeof(t_philosopher) * sim->number_of_philos);
	sim->state = malloc(sizeof(pthread_mutex_t));
	if (!sim->state)
	{
		return (1);
	}
	memset(sim->state, 0, sizeof(pthread_mutex_t));
	sim->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!sim->print_lock)
	{
		return (1);
	}
	memset(sim->print_lock, 0, sizeof(pthread_mutex_t));
	return (0);
}