/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:14:45 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/24 15:33:00 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_sleep(t_philo *philo, int time_ms)
{
	const int	check_ms = 60;

	while (time_ms > 0)
	{
		if (ft_check_death(philo))
			break ;
		if (time_ms < check_ms)
			usleep((time_ms % check_ms) * 1000);
		else
			usleep(check_ms * 1000);
		time_ms -= check_ms;
	}
}

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
long	ft_gcts(t_philo *philo)
{
	return (ft_currtime() - philo->data.st);
}
