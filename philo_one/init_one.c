/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:25:13 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/01 18:40:58 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init_main_struct(t_main *str_main)
{
	g_error = -1;
	g_enough_eat = str_main->phil_num;
	if (!(str_main->thread = (pthread_t *)malloc(str_main->phil_num
	* sizeof(pthread_t))))
		return (1);
	if (!(str_main->mutex = (pthread_mutex_t *)malloc(str_main->phil_num
	* sizeof(pthread_mutex_t))))
		return (1);
	if (!(str_main->philosopher = (t_philosopher *)malloc(str_main->phil_num *
	sizeof(t_philosopher))))
		return (1);
	return (0);
}
