#include "../include/philosophers.h"

// Struct to calculate the time from the UNIX epoch in milliseconds
// 1 second = 1 000 milliseconds = 1 000 000 microseconds

//mesure time in milliseconds
long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

//custome more precise then usleep function
void	precise_sleep(int ms)
{
	struct timeval start;
	struct timeval end;
    long long elapsed_time;

	elapsed_time = 0;
    gettimeofday(&start, NULL);
    while (elapsed_time < ms)
    {
        usleep(10);
        gettimeofday(&end, NULL);
        elapsed_time = (end.tv_sec - start.tv_sec) * 1000LL + (end.tv_usec - start.tv_usec) / 1000;
    }
}
