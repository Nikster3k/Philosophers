/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:34:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/16 16:42:25 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_solo(void *philo_void)
{
	t_philo	*philo;

	philo = philo_void;
	philo->lasteat = ft_currtime();
	ft_philo_sleep(philo, philo->data.ttd);
	ft_philo_die(philo);
	return (NULL);
}

int	ft_philo_check_death(t_philo *philo)
{
	return (ft_currtime() - philo->lasteat >= philo->data.ttd);
}

void	ft_philo_die(t_philo *philo)
{
	if (ft_get_philo_state(philo) == RUNNING)
		ft_print_action("died", philo);
	ft_set_philo_state(philo, TERMINATE);
}

void	ft_philo_sleep(t_philo *philo, int sleep_ms)
{
	long	max_sleep;

	max_sleep = ft_currtime() + sleep_ms;
	while (max_sleep >= ft_currtime()
		&& ft_get_philo_state(philo) != TERMINATE)
	{
		usleep(1000);
		if (ft_philo_check_death(philo))
		{
			ft_philo_die(philo);
			return ;
		}
	}
}
