/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:14:45 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/05 17:55:56 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_tvtms(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

long	ft_currtime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (ft_tvtms(&tv));
}

//get current time from start
long	ft_gcts(long start)
{
	return (ft_currtime() - start);
}

void	ft_print_mutlti(char *str, long timestamp, int nbr)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	printf("%lu %i %s\n", timestamp, nbr, str);
	pthread_mutex_unlock(&mutex);
}
