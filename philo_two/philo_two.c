
#include "philo_two.h"



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