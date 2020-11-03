/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:45:12 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 20:46:40 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			put_time(t_philosopher *arg)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
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

int			print_out(int index, char *str)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		return (1);
	if (g_error == -1)
		if (str_out((time.tv_sec - g_sim_start.tv_sec) * MIL_MIC
		+ (time.tv_usec - g_sim_start.tv_usec) / MIL_MIC,
		index + 1, str))
		{
			write(1, "Malloc error\n", 13);
			return (1);
		}
	return (0);
}

void		*check_death(void *args)
{
	t_philosopher	*philosopher;
	struct timeval	time;

	philosopher = (t_philosopher *)args;
	if (gettimeofday(&time, NULL))
		return (NULL);
	while (((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC +
	(time.tv_usec - philosopher->eating_time.tv_usec) / MIL_MIC)
	< g_time_to_die)
	{
		if (usleep(200))
			return (NULL);
		if (gettimeofday(&time, NULL))
			return (NULL);
	}
	if (str_out((time.tv_sec - g_sim_start.tv_sec) * MIL_MIC +
	(time.tv_usec - g_sim_start.tv_usec) / MIL_MIC,
	philosopher->index + 1, " died\n"))
	{
		write(1, "Malloc error\n", 13);
		return (NULL);
	}
	g_error = philosopher->index;
	return (NULL);
}
