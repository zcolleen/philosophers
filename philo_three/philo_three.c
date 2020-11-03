/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:02:53 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/03 15:14:50 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*sem_eating(void *args)
{
	t_philosopher	*arg;
	pthread_t		death_check;

	arg = (t_philosopher *)args;
	put_time(arg);
	if (arg->index % 2 == 1)
		custom_sleep(g_time_to_eat);
	if (pthread_create(&death_check, NULL, check_death, (void *)arg))
		exit(1);
	while (g_error == -1)
		algorithm(arg);
	if (pthread_join(death_check, NULL))
		exit(1);
	exit(0);
}

void	wait_pid(t_main *main)
{
	int stop;
	int status;
	int	i;

	i = 0;
	stop = main->phil_num;
	while (stop)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 2)
		{
			i = 0;
			while (i < main->phil_num)
			{
				if (kill(main->pids[i], 9))
					exit(1);
				i++;
			}
			stop = 0;
		}
		else
			stop--;
	}
}

void	init_forks(t_main *main, int i)
{
	pid_t	proc;

	while (i < main->phil_num)
	{
		if ((proc = fork()) == -1)
			exit(1);
		if (proc == 0)
			sem_eating(&main->philosopher[i]);
		main->pids[i] = proc;
		i += 2;
	}
}

int		sem_simulation(t_main *main)
{
	int		i;

	i = 0;
	while (i < main->phil_num)
	{
		main->philosopher[i].index = i;
		main->philosopher[i].count_eat = -1;
		main->philosopher[i].eating_time.tv_sec = 0;
		main->philosopher[i].eating_time.tv_usec = 0;
		i++;
	}
	if (gettimeofday(&sim_start, NULL))
		exit(1);
	init_forks(main, 0);
	init_forks(main, 1);
	wait_pid(main);
	sem_unlink("zcolleen");
	sem_close(g_sem);
	return (0);
}

int		main(int argc, char **argv)
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
