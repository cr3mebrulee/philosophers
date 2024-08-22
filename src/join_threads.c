
#include "../include/philosophers.h"

int join_threads(t_simulation *sim)
{
    int i;

    i = 0;
    while (i < sim->number_of_philos)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != 0)
		{
			printf("Failed to join thread");
			initiate_termination(sim, 1, 1, 1);
			return (1);
		}
		i++;
	}
	// if (pthread_join(sim->monitor_thread, NULL) != 0)
	// {
	// 	printf("Failed to join monitor thread\n");
	// 	initiate_termination(sim, 1, 1, 1);
	// 	return (1);
	// }
    return (0);
}