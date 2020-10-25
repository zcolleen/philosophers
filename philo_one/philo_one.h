

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define P_NUMBER 11
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct	s_parced
{
	int 		phil_num;
	useconds_t	time_to_die;
	useconds_t	time_to_sleep;
	useconds_t	time_to_eat;
}				t_parced;

typedef struct		s_main
{
	pthread_t		*thread;
	pthread_mutex_t *mutex;
	t_parced 		*parced;
	int 			left_fork;
	int 			right_fork;
	time_t 			sec;
	suseconds_t 	usec;
}					t_main;

int init_main_struct(t_main *str_main);

#endif
