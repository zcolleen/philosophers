
#include "philo_three.h"

void 		print_out(int index, char *str)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (error == -1)
		str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec - sim_start.tv_usec) / MIL_MIC, index + 1, str);
}

void 		*check_death(void *args)
{
	t_philosopher 	*philosopher;
	struct timeval	time;

	philosopher = (t_philosopher *)args;
	gettimeofday(&time, NULL);
	while (((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC + (time.tv_usec - philosopher->eating_time.tv_usec) / MIL_MIC) < time_to_die)
	{
		usleep(200);
		gettimeofday(&time, NULL);
		//printf("%ld\n", ((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC + (time.tv_usec - philosopher->eating_time.tv_usec) / MIL_MIC));
		//usleep(200);
	}
	//printf("%ld\n", ((time.tv_sec - philosopher->eating_time.tv_sec) * MIL_MIC + (time.tv_usec - philosopher->eating_time.tv_usec) / MIL_MIC));
	str_out((time.tv_sec - sim_start.tv_sec) * MIL_MIC + (time.tv_usec - sim_start.tv_usec) / MIL_MIC, philosopher->index + 1, " has died\n");
	exit(1);
}

void 		put_time(t_philosopher *arg)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	arg->eating_time.tv_sec = time.tv_sec;
	arg->eating_time.tv_usec = time.tv_usec;
	arg->count_eat++;
	if (!(arg->count_eat ^ num_of_eat))
	{
		sem_post(sem);
		sem_post(sem);
		exit(0);
	}
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

void 	*sem_eating(void *args)
{
	t_philosopher 	*arg;
	pthread_t 		death_check;

	arg = (t_philosopher *)args;
	put_time(arg);
	pthread_create(&death_check, NULL, check_death, (void *)arg);
	while (error == -1)
	{
		sem_wait(sem);
		print_out(arg->index, " has taken left fork\n");
		sem_wait(sem);
		print_out(arg->index, " has taken right fork\n");
		print_out(arg->index, " is eating\n");
		put_time(arg);
		custom_sleep(time_to_eat);
		sem_post(sem);
		sem_post(sem);
		print_out(arg->index, " is sleeping\n");
		custom_sleep(time_to_sleep);
		print_out(arg->index, " is thinking\n");
	}
	pthread_join(death_check, NULL);
	exit(0);
}


void 	ft_kill(t_main *main)
{
	int i;

	i = 0;
	while (i < main->phil_num)
	{
		kill(main->pids[i], 9);
		i++;
	}
}


void 	wait_pid(t_main *main)
{
	int stop;
	int status;

	stop = main->phil_num;
	while (stop)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			ft_kill(main);
			stop = 0;
		}
		else
			stop--;
	}
}

int 	sem_simulation(t_main *main)
{
	int		i;
	pid_t	proc;

	i = 0;
	while (i < main->phil_num)
	{
		main->philosopher[i].index = i;
		main->philosopher[i].count_eat = -1;
		main->philosopher[i].eating_time.tv_sec = 0;
		main->philosopher[i].eating_time.tv_usec = 0;
		i++;
	}
	i = 0;
	gettimeofday(&sim_start, NULL);
	while (i < main->phil_num)
	{
		if ((proc = fork()) == -1)
			exit(1);
		if (proc == 0)
			sem_eating(&main->philosopher[i]);
		main->pids[i] = proc;
		i++;
	}
	wait_pid(main);
	sem_unlink("zcolleen");
	sem_close(sem);
	return (0);
}

int 	main(int argc, char **argv)
{
	t_main			main;
	t_philosopher 	philosopher;

	main.philosopher = &philosopher;
	if (parce_arg(argc, argv, &main))
		return (1);
	if (init_sem(&main) || init_main_struct(&main) || sem_simulation(&main))
		return (1);
	return (0);
}