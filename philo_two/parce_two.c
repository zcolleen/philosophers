/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:32:40 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 20:38:56 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int			ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}

static int			ft_atoi(const char *nptr)
{
	int		i;
	long	d;

	d = 0;
	i = 0;
	while (nptr[i] != '\0')
	{
		if (d * 10 < d)
			return (-1);
		if (!ft_isdigit(nptr[i]))
			return ((int)d);
		d = d * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)d);
}

static void			put_arg(int j, t_main *main, char *str)
{
	if (j == 1)
		main->phil_num = ft_atoi(str);
	else if (j == 2)
		g_time_to_die = ft_atoi(str);
	else if (j == 3)
		g_time_to_eat = ft_atoi(str);
	else if (j == 4)
		g_time_to_sleep = ft_atoi(str);
	else if (j == 5)
		g_num_of_eat = ft_atoi(str);
}

static int			argument_check(char *str, int j, t_main *main)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
		{
			write(1, "Invalid argument\n", 17);
			return (1);
		}
		i++;
	}
	put_arg(j, main, str);
	return (0);
}

int					parce_arg(int argc, char **argv, t_main *main)
{
	int j;

	j = 1;
	g_num_of_eat = -1;
	if (argc != 6 && argc != 5)
	{
		write(1, "Wrong number of arguments\n", 26);
		return (1);
	}
	while (j < argc)
	{
		if (argument_check(argv[j], j, main))
			return (1);
		j++;
	}
	return (0);
}
