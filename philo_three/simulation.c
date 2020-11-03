/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:13:22 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/03 16:07:46 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	print_out(int index, char *str)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		exit(1);
	if (g_error == -1)
		str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec -
		sim_start.tv_usec) / MIL_MIC, index + 1, str);
}

void	*check_death(void *args)
{
	t_philosopher	*philosopher;
	struct timeval	time;

	philosopher = (t_philosopher *)args;
	if (gettimeofday(&time, NULL))
		exit(1);
	while (((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC +
	(time.tv_usec - philosopher->eating_time.tv_usec)
	/ MIL_MIC) < g_time_to_die)
	{
		if (usleep(200))
			exit(1);
		if (gettimeofday(&time, NULL))
			exit(1);
	}
	str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec
	- sim_start.tv_usec) / MIL_MIC, philosopher->index + 1, " died\n");
	exit(2);
}

void	put_time(t_philosopher *arg)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		exit(1);
	arg->eating_time.tv_sec = time.tv_sec;
	arg->eating_time.tv_usec = time.tv_usec;
	arg->count_eat++;
	if (!(arg->count_eat ^ g_num_of_eat))
	{
		if (sem_post(g_sem))
			exit(1);
		if (sem_post(g_sem))
			exit(1);
		exit(0);
	}
}

void	custom_sleep(long sleep_time)
{
	struct timeval	time;
	long			end_time;

	if (gettimeofday(&time, NULL))
		exit(1);
	end_time = time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC + sleep_time;
	while ((time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC) ^ end_time)
	{
		if (gettimeofday(&time, NULL))
			exit(1);
		if (usleep(200))
			exit(1);
	}
}

void	algorithm(t_philosopher *arg)
{
	if (sem_wait(g_sem))
		exit(1);
	print_out(arg->index, " has taken a fork\n");
	if (sem_wait(g_sem))
		exit(1);
	print_out(arg->index, " has taken a fork\n");
	print_out(arg->index, " is eating\n");
	put_time(arg);
	custom_sleep(g_time_to_eat);
	if (sem_post(g_sem) || sem_post(g_sem))
		exit(1);
	print_out(arg->index, " is sleeping\n");
	custom_sleep(g_time_to_sleep);
	print_out(arg->index, " is thinking\n");
}
