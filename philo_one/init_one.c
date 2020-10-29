
#include "philo_one.h"

int init_main_struct(t_main *str_main)
{
	error = -1;
	enough_eat = str_main->phil_num;
	if (!(str_main->thread = (pthread_t *)malloc(str_main->phil_num
	* sizeof(pthread_t))))
		return (1);
//	memset(str_main->thread, 0, str_main->phil_num);
	if (!(str_main->mutex = (pthread_mutex_t *)malloc(str_main->phil_num
	* sizeof(pthread_mutex_t))))
		return (1);
//	memset(str_main->mutex, 0, str_main->phil_num);
	if (!(str_main->philosopher = (t_philosopher *)malloc(str_main->phil_num * sizeof(t_philosopher))))
		return (1);
//	memset(str_main->philosopher, 0, str_main->phil_num);
	return (0);
}

