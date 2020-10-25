
#include "philo_one.h"

void *eating(void *args)
{
	t_main	*arg;

	arg = (t_main *)args;
	write(1, "philo started dinner\n", 21);
	write(1, "locked\n", 7);
	pthread_mutex_lock(&(arg->mutex[arg->right_fork]));
	write(1, "has taken a fork\n", 21);
	pthread_mutex_lock(&(arg->mutex[arg->left_fork]));
	write(1, "has taken a fork\n", 21);
	write(1, "philosopher is eating\n", 22);
	usleep(arg->parced->time_to_eat);
	pthread_mutex_unlock(&(arg->mutex[arg->right_fork]));
	pthread_mutex_unlock(&(arg->mutex[arg->left_fork]));
	write(1, "philosopher is eating\n", 22);
	usleep(arg->parced->time_to_sleep);
	return (NULL);
}

int		init_thread(t_main *main, int i)
{
	if (i == 0)
		main->left_fork = main->parced->phil_num - 1;
	else
		main->left_fork = 0;
	while (i < main->parced->phil_num)
	{
		main->right_fork = i;
		if (pthread_create(&(main->thread[i]), NULL, eating, (void *)main))
			return (1);
		main->left_fork = i + 1;
		i += 2;
	}
	return (0);
}

int		simulation(t_main *main)
{
	int i;

	i = 0;
	while (i < main->parced->phil_num)
	{
		if (pthread_mutex_init(&(main->mutex[i]), NULL))
			return (1);
		i++;
	}
	if (init_thread(main, 0) || init_thread(main, 1))
		return (1);
	i = 0;
	while (i < main->parced->phil_num)
	{
		pthread_join(main->thread[i], NULL);
		i++;
	}
	return (0);
}

int 	main()
{
	t_main		main;
	t_parced	parced;


	main.parced = &parced;
	if (init_main_struct(&main) || simulation(&main))
		return (-1);
	return (0);
}