

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define MIL_MIC 1000
# define U_SEC 1000000
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <signal.h>

sem_t 	*sem;
int 	error;
long 	time_to_sleep;
long 	time_to_eat;
long 	time_to_die;
struct timeval sim_start;
int 	num_of_eat;
int 	enough_eat;

typedef struct 				s_philosopher
{
	struct timeval			eating_time;
	int 					index;
	int 					count_eat;
}							t_philosopher;

typedef struct				s_main
{
	int 					phil_num;
	pthread_t				*death_thr;
	int 					thread_count;
	t_philosopher 			*philosopher;
	pid_t 					*pids;
}							t_main;

int 		init_main_struct(t_main *str_main);
int			str_out(long timestam, int philo_num, char *str);
int 		parce_arg(int argc, char **argv, t_main *main);
int 		init_sem(t_main *main);




#endif
