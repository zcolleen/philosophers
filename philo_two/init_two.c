

#include "philo_two.h"

int init_main_struct(t_main *str_main)
{
	error = -1;
	enough_eat = str_main->phil_num;
	if (!(str_main->thread = (pthread_t *)malloc(str_main->phil_num
	* sizeof(pthread_t))))
		return (1);
	if (!(str_main->philosopher = (t_philosopher *)malloc(str_main->phil_num * sizeof(t_philosopher))))
		return (1);
	return (0);
}

int 	init_sem(t_main *main)
{
	sem_unlink("zcolleen");
	if ((sem = sem_open("zcolleen", O_CREAT | O_EXCL, 0777, main->phil_num)) == SEM_FAILED)
		return (1);
	return (0);
}