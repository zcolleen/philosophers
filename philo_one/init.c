
#include "philo_one.h"

int init_main_struct(t_main *str_main)
{
	if (!(str_main->thread = (pthread_t *)malloc(P_NUMBER * sizeof(pthread_t))))
		return (-1);
	memset(str_main->thread, 0, P_NUMBER);
	if (!(str_main->mutex = (pthread_mutex_t *)malloc(P_NUMBER * sizeof(pthread_mutex_t))))
		return (-1);
	memset(str_main->mutex, 0, P_NUMBER);
	str_main->phil_num = P_NUMBER;
	return (0);
}

