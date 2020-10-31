

#include "philo_three.h"

int init_main_struct(t_main *str_main)
{
	error = -1;
	enough_eat = str_main->phil_num;
	str_main->thread_count = -1;
	if (!(str_main->death_thr = (pthread_t *)malloc(str_main->phil_num
	* sizeof(pthread_t))))
		return (1);
	if (!(str_main->philosopher = (t_philosopher *)malloc(str_main->phil_num * sizeof(t_philosopher))))
		return (1);
	if (!(str_main->pids = (pid_t *)malloc(str_main->phil_num * sizeof(pid_t))))
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