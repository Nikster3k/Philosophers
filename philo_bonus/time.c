/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:14:45 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/12 17:40:20 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
