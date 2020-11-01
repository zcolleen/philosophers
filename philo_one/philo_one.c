/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:42:25 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 18:41:22 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		*eating(void *args)
{
	t_philosopher		*arg;
	pthread_t			death_check;

	arg = (t_philosopher *)args;
	if (put_time(arg) ||
	pthread_create(&death_check, NULL, check_death, (void *)arg))
		return (NULL);
	if (arg->index % 2 == 1)
		if (custom_sleep(g_time_to_eat))
			return (NULL);
	while (g_error == -1)
	{
		if (algorithm(arg))
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
		NULL, eating, (void *)&main->philosopher[i]))
			return (1);
		i += 2;
	}
	return (0);
}

void		init_philos(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->phil_num)
	{
		main->philosopher[i].index = i;
		main->philosopher[i].count_eat = -1;
		main->philosopher[i].left_fork = &(main->mutex[i]);
		main->philosopher[i].eating_time.tv_sec = 0;
		main->philosopher[i].eating_time.tv_usec = 0;
		i++;
		if (i < main->phil_num)
			main->philosopher[i - 1].right_fork = &(main->mutex[i]);
	}
	main->philosopher[i - 1].right_fork = &(main->mutex[0]);
}

int			simulation(t_main *main)
{
	int i;

	i = 0;
	while (i < main->phil_num)
	{
		if (pthread_mutex_init(&(main->mutex[i]), NULL))
			return (1);
		i++;
	}
	init_philos(main);
	if (gettimeofday(&sim_start, NULL) || init_thread(main, 0)
	|| init_thread(main, 1))
		return (1);
	i = 0;
	while (i < main->phil_num)
	{
		if (pthread_join(main->thread[i], NULL) ||
		pthread_mutex_destroy(&main->mutex[i]))
			return (1);
		i++;
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_main							main;
	t_philosopher					philosopher;

	main.philosopher = &philosopher;
	if (parce_arg(argc, argv, &main))
		return (1);
	if (init_main_struct(&main) || simulation(&main))
		return (1);
	return (0);
}
