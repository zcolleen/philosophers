/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:36:15 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 18:46:12 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define P_NUMBER 4
# define T_SLEEP 200
# define T_DIE 410
# define T_EAT 200
# define MIL_MIC 1000
# define U_SEC 1000000
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

int							g_error;
long						g_time_to_sleep;
long						g_time_to_eat;
long						g_time_to_die;
struct timeval				sim_start;
int							g_num_of_eat;
int							g_enough_eat;

typedef struct				s_philosopher
{
	struct timeval			eating_time;
	int						index;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	int						count_eat;
}							t_philosopher;

typedef struct				s_main
{
	int						phil_num;
	pthread_t				*thread;
	pthread_mutex_t			*mutex;
	t_philosopher			*philosopher;
}							t_main;

int							init_main_struct(t_main *str_main);
int							str_out(long timestam, int philo_num, char *str);
int							parce_arg(int argc, char **argv, t_main *main);
void						*check_death(void *args);
int							algorithm(t_philosopher *arg);
int							custom_sleep(long sleep_time);
int							put_time(t_philosopher *arg);

#endif
