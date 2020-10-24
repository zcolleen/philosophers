

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define P_NUMBER 100
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct		s_main
{
	pthread_t		*thread;
	pthread_mutex_t *mutex;
	pthread_mutex_t *philo_lock;
	int 			phil_num;
	int 			left_fork;
	int 			right_fork;
}					t_main;

int init_main_struct(t_main *str_main);

#endif
