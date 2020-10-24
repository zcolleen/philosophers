
#include "philo_one.h"

int init_main_struct(t_main *str_main)
{
	str_main->phil_num = P_NUMBER;
	if (!(str_main->thread = (pthread_t *)malloc(str_main->phil_num * sizeof(pthread_t))))
		return (1);
	memset(str_main->thread, 0, str_main->phil_num);
	if (!(str_main->mutex = (pthread_mutex_t *)malloc(str_main->phil_num * sizeof(pthread_mutex_t))))
		return (1);
	memset(str_main->mutex, 0, str_main->phil_num);
	if (!(str_main->philo_lock = (pthread_mutex_t *)malloc(str_main->phil_num * sizeof(pthread_mutex_t))))
		return (-1);
	memset(str_main->philo_lock, 0, str_main->phil_num);
	str_main->left_fork = 0;
	str_main->right_fork = 0;
	return (0);
}

