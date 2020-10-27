
#include "philo_one.h"

void 		print_out(int index, char *str)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (error == -1)
		str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec - sim_start.tv_usec) / MIL_MIC, index, str);
	else if (error != -2)
	{
		str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec - sim_start.tv_usec) / MIL_MIC, error, " has died\n");
		error = -2;
	}
//	(error == -1) ? str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec - sim_start.tv_usec) / MIL_MIC, index, str) : 1;
}

void 		*check_death(void *args)
{
	t_philosopher 	*philosopher;
	struct timeval	time;

	philosopher = (t_philosopher *)args;
	gettimeofday(&time, NULL);
	while ((time.tv_sec - philosopher->eating_time.tv_sec) * U_SEC + (time.tv_usec - philosopher->eating_time.tv_usec) < time_to_die * MIL_MIC)
	{
		gettimeofday(&time, NULL);
		usleep(200);
	}
	error = philosopher->index;
	return (NULL);
}

void 		put_time(t_philosopher *arg)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	arg->eating_time.tv_sec = time.tv_sec;
	arg->eating_time.tv_usec = time.tv_usec;
}

void 		custom_sleep(long sleep_time)
{
	struct timeval time;
	long end_time;

	gettimeofday(&time, NULL);
	end_time = time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC + sleep_time;
	while ((time.tv_sec * MIL_MIC + time.tv_usec / MIL_MIC) ^ end_time)
	{
		gettimeofday(&time, NULL);
		usleep(200);
	}
}

void		*eating(void *args)
{
	t_philosopher 	*arg;
	pthread_t 		death_check;

	arg = (t_philosopher *)args;
	pthread_create(&death_check, NULL, check_death, (void *)arg);
	while (error == -1)
	{
		pthread_mutex_lock(&arg->right_fork);
		print_out(arg->index, " has taken a fork\n");
		pthread_mutex_lock(&(arg->left_fork));
		print_out(arg->index, " has taken a fork\n");
		put_time(arg);
		print_out(arg->index, " is eating\n");
		custom_sleep(time_to_eat);
		pthread_mutex_unlock(&(arg->right_fork));
		pthread_mutex_unlock(&(arg->left_fork));
		print_out(arg->index, " is sleeping\n");
		custom_sleep(time_to_sleep);
		print_out(arg->index, " is thinking\n");
	}
	pthread_join(death_check, NULL);
	return (NULL);
}

int		init_thread(t_main *main, int i)
{
	while (i < main->phil_num && error == -1)
	{
		if (pthread_create(&(main->thread[i]), NULL, eating, (void *)&main->philosopher[i]))
			return (1);
		i += 2;
	}
	return (0);
}

int		simulation(t_main *main)
{
	int i;

	i = 0;
	while (i < main->phil_num)
	{
		if (pthread_mutex_init(&(main->mutex[i]), NULL))
			return (1);
		main->philosopher[i].index = (char)i;
		main->philosopher[i].right_fork = main->mutex[i];
		main->philosopher[i].eating_time.tv_sec = 0;
		main->philosopher[i].eating_time.tv_usec = 0;
		if (i >= 1)
			main->philosopher[i].left_fork = main->mutex[i - 1];
		i++;
	}
	main->philosopher[0].left_fork = main->mutex[i - 1];
	gettimeofday(&sim_start, NULL);
	if (init_thread(main, 0) || init_thread(main, 1))
		return (1);
	i = 0;
	while (i < main->phil_num)
	{
		pthread_join(main->thread[i], NULL);
		pthread_mutex_destroy(&main->mutex[i]);
		i++;
	}
	return (0);
}

int 	main()
{
	t_main		main;
	t_philosopher philosopher;

	main.philosopher = &philosopher;
	if (init_main_struct(&main) || simulation(&main))
		return (-1);
	return (0);
}