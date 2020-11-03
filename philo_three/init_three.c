/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:02:19 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/03 15:08:13 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	init_main_struct(t_main *str_main)
{
	g_error = -1;
	if (!(str_main->philosopher = (t_philosopher *)malloc(str_main->phil_num *
	sizeof(t_philosopher))))
		return (1);
	if (!(str_main->pids = (pid_t *)malloc(str_main->phil_num * sizeof(pid_t))))
		return (1);
	return (0);
}

int	init_sem(t_main *main)
{
	sem_unlink("zcolleen");
	if ((g_sem = sem_open("zcolleen", O_CREAT | O_EXCL,
	0777, main->phil_num)) == SEM_FAILED)
		return (1);
	return (0);
}
