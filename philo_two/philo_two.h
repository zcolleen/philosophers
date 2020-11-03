/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:36:04 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 20:47:24 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# define MIL_MIC 1000
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>

sem_t						*g_sem;
int							g_error;
long						g_time_to_sleep;
long						g_time_to_eat;
long						g_time_to_die;
struct timeval				g_sim_start;
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
	t_philosopher			*philosopher;
}							t_main;

int							init_main_struct(t_main *str_main);
int							str_out(long timestam, int philo_num, char *str);
int							parce_arg(int argc, char **argv, t_main *main);
int							init_sem(t_main *main);
void						*check_death(void *args);
int							print_out(int index, char *str);
int							put_time(t_philosopher *arg);

#endif
