/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:14:45 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/07 19:41:48 by nsassenb         ###   ########.fr       */
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

void	ft_print_multi(char *str, t_philo *philo)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (ft_get_philo_state(philo) != RUNNING)
		return ;
	pthread_mutex_lock(&mutex);
	printf("% -8ld % -5i %s\n", ft_gcts(philo->data.st), philo->nbr, str);
	pthread_mutex_unlock(&mutex);
}
