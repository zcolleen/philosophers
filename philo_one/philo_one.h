

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define P_NUMBER 5
# define T_SLEEP 200
# define T_DIE 800
# define T_EAT 200
# define MIL_MIC 1000
# define U_SEC 1000000
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

char error;
long time_to_sleep;
long time_to_eat;
long time_to_die;
struct timeval sim_start;

typedef struct 				s_philosopher
{
	struct timeval			eating_time;
	char 					index;
	pthread_mutex_t 		left_fork;
	pthread_mutex_t 		right_fork;
	struct timeval			sim_time;
}							t_philosopher;

typedef struct				s_main
{
	int 					phil_num;
	pthread_t				*thread;
	pthread_mutex_t 		*mutex;
	t_philosopher 			*philosopher;
}							t_main;

int			init_main_struct(t_main *str_main);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
int			str_out(long timestam, int philo_num, char *str);



#endif
