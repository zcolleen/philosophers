/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_out_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcolleen <zcolleen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:08:40 by zcolleen          #+#    #+#             */
/*   Updated: 2020/11/03 15:10:27 by zcolleen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int		counter(unsigned long n)
{
	int s;

	s = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		s++;
	}
	return (s);
}

static void		record(char *ptr, unsigned long n, int count_num)
{
	int i;

	i = count_num;
	ptr[i] = '\0';
	i--;
	while (n / 10 != 0)
	{
		ptr[i] = (char)(n % 10 + '0');
		n = n / 10;
		i--;
	}
	ptr[i] = (char)(n % 10 + '0');
}

int				put_in_buf(const char *ptr,
const char *ptr_2, char *to_write, const char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (ptr[count] != '\0')
	{
		to_write[count] = ptr[count];
		count++;
	}
	to_write[count++] = ' ';
	while (ptr_2[i] != '\0')
	{
		to_write[count] = ptr_2[i];
		count++;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		to_write[count] = str[i];
		count++;
		i++;
	}
	return (count);
}

int				str_out(long timestam, int philo_num, char *str)
{
	char		*ptr;
	size_t		count;
	char		*ptr_2;
	char		*to_write;

	count = counter(philo_num);
	if (!(ptr = (char *)malloc(sizeof(char) * (count + 1))))
		exit(1);
	record(ptr, philo_num, count);
	count = counter(timestam);
	if (!(ptr_2 = (char *)malloc(sizeof(char) * (count + 1))))
		exit(1);
	record(ptr_2, timestam, count);
	count = ft_strlen(ptr) + ft_strlen(ptr_2) + ft_strlen(str) + 1;
	if (!(to_write = (char *)malloc(sizeof(char) * (count + 1))))
		exit(1);
	to_write[count] = '\0';
	count = put_in_buf(ptr_2, ptr, to_write, str);
	write(1, to_write, count);
	free(ptr);
	free(ptr_2);
	free(to_write);
	return (0);
}
