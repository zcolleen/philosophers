/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:05:15 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/03 15:16:53 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# define MIL_MIC 1000
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

sem_t						*g_sem;
int							g_error;
long						g_time_to_sleep;
long						g_time_to_eat;
long						g_time_to_die;
struct timeval				sim_start;
int							g_num_of_eat;

typedef struct				s_philosopher
{
	struct timeval			eating_time;
	int						index;
	int						count_eat;
}							t_philosopher;

typedef struct				s_main
{
	int						phil_num;
	t_philosopher			*philosopher;
	pid_t					*pids;
}							t_main;

int							init_main_struct(t_main *str_main);
int							str_out(long timestam, int philo_num, char *str);
int							parce_arg(int argc, char **argv, t_main *main);
int							init_sem(t_main *main);
void						*check_death(void *args);
void						custom_sleep(long sleep_time);
void						put_time(t_philosopher *arg);
void						algorithm(t_philosopher *arg);

#endif
