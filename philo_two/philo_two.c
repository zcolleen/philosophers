/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:28:25 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 20:46:56 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			custom_sleep(long sleep_time)
{
	struct timeval	time;
	long			end_time;

	if (gettimeofday(&time, NULL))
		return (1);
	end_time = time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC + sleep_time;
	while ((time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC) ^ end_time)
	{
		if (gettimeofday(&time, NULL))
			return (1);
		if (usleep(200))
			return (1);
	}
	return (0);
}

void		*sem_eating(void *args)
{
	t_philosopher	*arg;
	pthread_t		death_check;

	arg = (t_philosopher *)args;
	if (put_time(arg))
		return (NULL);
	if (pthread_create(&death_check, NULL, check_death, (void *)arg))
		return (NULL);
	if (arg->index % 2 == 1)
		if (custom_sleep(g_time_to_eat))
			return (NULL);
	while (g_error == -1)
	{
		if (sem_wait(g_sem) || print_out(arg->index, " has taken a fork\n") ||
		sem_wait(g_sem) || print_out(arg->index, " has taken a fork\n") ||
		print_out(arg->index, " is eating\n") || put_time(arg) ||
		custom_sleep(g_time_to_eat) || sem_post(g_sem) ||
		sem_post(g_sem) || print_out(arg->index, " is sleeping\n") ||
		custom_sleep(g_time_to_sleep) ||
		print_out(arg->index, " is thinking\n"))
			return (NULL);
	}
	if (pthread_join(death_check, NULL))
		return (NULL);
	return (NULL);
}

int			init_thread(t_main *main, int i)
{
	while (i < main->phil_num)
	{
		if (pthread_create(&(main->thread[i]),
			NULL, sem_eating, (void *)&main->philosopher[i]))
			return (1);
		i += 2;
	}
	return (0);
}

int			sem_simulation(t_main *main)
{
	int i;

	i = 0;
	while (i < main->phil_num)
	{
		main->philosopher[i].index = i;
		main->philosopher[i].count_eat = -1;
		main->philosopher[i].eating_time.tv_sec = 0;
		main->philosopher[i].eating_time.tv_usec = 0;
		i++;
	}
	if (gettimeofday(&g_sim_start, NULL))
		return (1);
	if (init_thread(main, 0) ||
	init_thread(main, 1))
		return (1);
	i = 0;
	while (i++ < main->phil_num)
	{
		if (pthread_join(main->thread[i], NULL))
			return (1);
	}
	sem_unlink("zcolleen");
	sem_close(g_sem);
	return (0);
}

int			main(int argc, char **argv)
{
	t_main			main;
	t_philosopher	philosopher;

	main.philosopher = &philosopher;
	if (parce_arg(argc, argv, &main))
		return (1);
	if (init_sem(&main) || init_main_struct(&main) || sem_simulation(&main))
		return (1);
	return (0);
}
