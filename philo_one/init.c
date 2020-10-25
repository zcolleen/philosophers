
#include "philo_one.h"

int init_main_struct(t_main *str_main)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	str_main->sec = time.tv_sec;
	str_main->usec = time.tv_usec;
	str_main->parced->phil_num = P_NUMBER;
	str_main->parced->time_to_die = 10;
	str_main->parced->time_to_sleep = 10;
	str_main->parced->time_to_die = 10;
	if (!(str_main->thread = (pthread_t *)malloc(str_main->parced->phil_num
	* sizeof(pthread_t))))
		return (1);
	memset(str_main->thread, 0, str_main->parced->phil_num);
	if (!(str_main->mutex = (pthread_mutex_t *)malloc(str_main->parced->phil_num
	* sizeof(pthread_mutex_t))))
		return (1);
	memset(str_main->mutex, 0, str_main->parced->phil_num);
	str_main->left_fork = 0;
	str_main->right_fork = 0;
	return (0);
}

