
#include "philo_one.h"

int init_main_struct(t_main *str_main)
{
	str_main->phil_num = P_NUMBER;
	time_to_die = T_DIE;
	time_to_sleep = T_SLEEP;
	time_to_eat = T_EAT;
	error = -1;
	if (!(str_main->thread = (pthread_t *)malloc(str_main->phil_num
	* sizeof(pthread_t))))
		return (1);
	memset(str_main->thread, 0, str_main->phil_num);
	if (!(str_main->mutex = (pthread_mutex_t *)malloc(str_main->phil_num
	* sizeof(pthread_mutex_t))))
		return (1);
	memset(str_main->mutex, 0, str_main->phil_num);
	if (!(str_main->philosopher = (t_philosopher *)malloc(str_main->phil_num * sizeof(t_philosopher))))
		return (1);
	memset(str_main->philosopher, 0, str_main->phil_num);
	return (0);
}

