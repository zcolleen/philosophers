
#include "philo_one.h"

void *eating(void *args)
{
	t_main *arg;

	arg = (t_main *)args;
	pthread_mutex_lock(&arg->mutex[arg->right_fork]);
	pthread_mutex_lock(&(arg->mutex[arg->left_fork]));
	write(1, "philosopher eating\n", 19);
	pthread_mutex_unlock(&arg->mutex[arg->left_fork]);
	pthread_mutex_unlock(&arg->mutex[arg->right_fork]);
	return (NULL);
}

int		simulation(t_main *main)
{
	int i;

	i = 0;
	while (i < main->phil_num)
	{
		if (pthread_mutex_init(&(main->mutex[i]), NULL) || pthread_mutex_init(&(main->philo_lock[i]), NULL))
			return (1);
		i++;
	}
	i = 0;
	main->left_fork = main->phil_num - 1;
	while (i < main->phil_num)
	{
		main->right_fork = i;
		if (pthread_create(&(main->thread[i]), NULL, eating, (void *)main))
			return (1);
		main->left_fork = i;
		i++;
	}
	i = 0;
	while (i < main->phil_num)
	{
		pthread_join(main->thread[i], NULL);
		i++;
	}
	return (0);
}

int 	main()
{
	t_main main;

	if (init_main_struct(&main) || simulation(&main))
		return (-1);
	return (0);
}