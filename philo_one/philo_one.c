
#include "philo_one.h"

void 		print_out(int index, char *str)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (error == -1)
		str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec - sim_start.tv_usec) / MIL_MIC, index, str);
}

void 		*check_death(void *args)
{
	t_philosopher 	*philosopher;
	struct timeval	time;

	philosopher = (t_philosopher *)args;
	gettimeofday(&time, NULL);
	//printf("%d\n", time_to_die);
	while (((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC + (time.tv_usec - philosopher->eating_time.tv_usec) / MIL_MIC) ^ time_to_die)
	{
		gettimeofday(&time, NULL);
		usleep(200);
	}
	printf("%ld\n", ((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC + (time.tv_usec - philosopher->eating_time.tv_usec) / MIL_MIC));
	str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec - sim_start.tv_usec) / MIL_MIC, philosopher->index, " has died\n");
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
	put_time(arg);
	pthread_create(&death_check, NULL, check_death, (void *)arg);
	while (error == -1)
	{
//		if (!(arg->index ^ 0))
//		{
//			pthread_mutex_lock(arg->right_fork);
//			print_out(arg->index, " has taken right fork\n");
//			pthread_mutex_lock(arg->left_fork);
//			print_out(arg->index, " has taken left fork\n");
//		}
//		else
//		{
			pthread_mutex_lock(arg->left_fork);
			//write(1, " has taken left fork\n", 21);
			print_out(arg->index, " has taken left fork\n");
			pthread_mutex_lock(arg->right_fork);
			//write(1, " has taken right fork\n", 22);
			print_out(arg->index, " has taken right fork\n");
//		}
		put_time(arg);
		//write(1, " is eating\n", 11);
		print_out(arg->index, " is eating\n");
		custom_sleep(time_to_eat);
		pthread_mutex_unlock(arg->right_fork);
		pthread_mutex_unlock(arg->left_fork);
		//write(1, " is sleeping\n", 13);
		print_out(arg->index, " is sleeping\n");
		custom_sleep(time_to_sleep);
		//write(1, " is thinking\n", 13);
		print_out(arg->index, " is thinking\n");
	}
	pthread_join(death_check, NULL);
	return (NULL);
}

int		init_thread(t_main *main, int i)
{
//	int i;
//
//	i = 0;
	while (i < main->phil_num)
	{
		if (pthread_create(&(main->thread[i]), NULL, eating, (void *)&main->philosopher[i]))
			return (1);
		//usleep(10);
		//i++;
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
		i++;
	}
	i = 0;
	while (i < main->phil_num)
	{
		main->philosopher[i].index = i;
		main->philosopher[i].left_fork = &(main->mutex[i]);
		main->philosopher[i].eating_time.tv_sec = 0;
		main->philosopher[i].eating_time.tv_usec = 0;
		i++;
		if (i < main->phil_num)
			main->philosopher[i - 1].right_fork = &(main->mutex[i]);
	}
	main->philosopher[i - 1].right_fork = &(main->mutex[0]);
//	if (main->philosopher[0].right_fork == main->philosopher[1].left_fork &&
//	main->philosopher[1].right_fork == main->philosopher[2].left_fork &&
//	main->philosopher[2].right_fork == main->philosopher[3].left_fork &&
//	main->philosopher[3].right_fork == main->philosopher[0].left_fork)
//		printf("ok");
//	else
//		printf("not ok");
	gettimeofday(&sim_start, NULL);
	if (init_thread(main, 0) || init_thread(main, 1))
		return (1);
//	if (init_thread(main, 1))
//		return (1);
	i = 0;
	while (i < main->phil_num)
	{
		pthread_join(main->thread[i], NULL);
		pthread_mutex_destroy(&main->mutex[i]);
		i++;
	}
	return (0);
}

int 	main(int argc, char **argv)
{
	t_main			main;
	t_philosopher 	philosopher;

	main.philosopher = &philosopher;
	if (parce_arg(argc, argv, &main))
		return (1);
	//printf("num of philos: |%d|\n time_to_die: |%ld|\n time_to_eat: |%ld|\n time_to_sleep: |%ld|\n num_of_eat: |%d|", main.phil_num, time_to_die, time_to_eat, time_to_sleep, num_of_eat);
	if (init_main_struct(&main) || simulation(&main))
		return (1);
	return (0);
}