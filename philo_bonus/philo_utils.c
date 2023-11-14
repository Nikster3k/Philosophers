/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:34:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/12 22:35:50 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_set_state(t_philo *philo, t_state new_state)
{
	sem_wait(philo->status);
	printf("SET STATE TO %i\n", new_state);
	philo->state = new_state;
	sem_post(philo->status);
}

int	ft_get_state(t_philo *philo)
{
	t_state	ret;
	
	sem_wait(philo->status);
	ret = philo->state;
	printf("GET STATE FROM %i\nState is %i\n", philo->nbr, ret);
	sem_post(philo->status);
	return (ret);
}

int	ft_philo_check_death(t_philo *philo)
{
	return (ft_currtime() - philo->lasteat >= philo->data.ttd);
}

void	ft_philo_die(t_philo *philo)
{
	if (ft_get_state(philo) == RUNNING)
		ft_print_action("died", philo);
	ft_set_state(philo, TERMINATE);
}

void	ft_philo_sleep(t_philo *philo, int sleep_ms)
{
	long	max_sleep;

	max_sleep = ft_currtime() + sleep_ms;
	while (max_sleep >= ft_currtime() && ft_get_state(philo) != TERMINATE)
	{
		usleep(1000);
		if (ft_philo_check_death(philo))
		{
			ft_philo_die(philo);
			return ;
		}
	}
}
