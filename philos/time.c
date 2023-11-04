/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:14:45 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/04 18:07:19 by nsassenb         ###   ########.fr       */
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

long	ft_gcts(long start)
{
	return (ft_currtime() - start);
}