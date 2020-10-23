

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define P_NUMBER 10
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct		s_main
{
	pthread_t		*thread;
	pthread_mutex_t *mutex;
	int 			phil_num;
}					t_main;

int init_main_struct(t_main *str_main);

#endif
