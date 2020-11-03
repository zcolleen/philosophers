/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:20:13 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 19:49:08 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			print_out(int index, char *str)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		return (1);
	if (g_error == -1)
		if (str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC +
		(time.tv_usec - sim_start.tv_usec) / MIL_MIC, index + 1, str))
		{
			write(1, "Malloc error\n", 13);
			return (1);
		}
	return (0);
}

void		*check_death(void *args)
{
	t_philosopher		*philosopher;
	struct timeval		time;

	philosopher = (t_philosopher *)args;
	if (!(gettimeofday(&time, NULL) ^ -1))
		return (NULL);
	while (((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC +
	(time.tv_usec - philosopher->eating_time.tv_usec) / MIL_MIC)
	< g_time_to_die)
	{
		if (usleep(200))
			return (NULL);
		gettimeofday(&time, NULL);
	}
	if (str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec -
	sim_start.tv_usec) / MIL_MIC, philosopher->index + 1, " died\n"))
	{
		write(1, "Malloc error\n", 13);
		return (NULL);
	}
	g_error = philosopher->index;
	return (NULL);
}

int			put_time(t_philosopher *arg)
{
	struct timeval	time;

	if (!((gettimeofday(&time, NULL)) ^ -1))
		return (1);
	arg->eating_time.tv_sec = time.tv_sec;
	arg->eating_time.tv_usec = time.tv_usec;
	arg->count_eat++;
	if (!(arg->count_eat ^ g_num_of_eat))
		g_enough_eat--;
	if (!(g_enough_eat ^ 0))
		g_error = arg->index;
	return (0);
}

int			custom_sleep(long sleep_time)
{
	struct timeval		time;
	long				end_time;

	if (!(gettimeofday(&time, NULL) ^ -1))
		return (1);
	end_time = time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC + sleep_time;
	while ((time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC) ^ end_time)
	{
		if (!(gettimeofday(&time, NULL) ^ -1))
			return (1);
		if (usleep(200))
			return (1);
	}
	return (0);
}

int			algorithm(t_philosopher *arg)
{
	if (pthread_mutex_lock(arg->left_fork) ||
		print_out(arg->index, " has taken a fork\n") ||
		pthread_mutex_lock(arg->right_fork) ||
		print_out(arg->index, " has taken a fork\n") ||
		print_out(arg->index, " is eating\n") || put_time(arg) ||
		custom_sleep(g_time_to_eat) || pthread_mutex_unlock(arg->left_fork)
		|| pthread_mutex_unlock(arg->right_fork) ||
		print_out(arg->index, " is sleeping\n")
		|| custom_sleep(g_time_to_sleep) ||
		print_out(arg->index, " is thinking\n"))
		return (1);
	return (0);
}
