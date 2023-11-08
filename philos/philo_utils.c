/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:34:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/08 19:24:32 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_check_death(t_philo *philo)
{
	return (ft_currtime() - philo->lasteat >= philo->data.ttd);
}

void	ft_philo_die(t_philo *philo)
{
	ft_print_multi("died", philo);
	ft_set_philo_state(philo, TERMINATE);
	ft_tryunlock(philo, philo->right);
	ft_tryunlock(philo, &philo->own);
}

void	ft_philo_wait(t_philo *philo, int sleep_ms)
{
	long	max_sleep;

	max_sleep = ft_currtime() + sleep_ms;
	while (max_sleep >= ft_currtime()
		&& ft_get_philo_state(philo) != TERMINATE)
	{
		usleep(1000);
		if (ft_philo_check_death(philo))
		{
			ft_set_philo_state(philo, TERMINATE);
			return ;
		}
	}
}
