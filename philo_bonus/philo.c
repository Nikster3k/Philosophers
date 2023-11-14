/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:34 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/14 20:37:00 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_try_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	ft_print_action("has taken a fork", philo);
	sem_wait(philo->forks);
	ft_print_action("has taken a fork", philo);
	if (ft_philo_check_death(philo))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		return (-1);
	}
	ft_print_action("is eating", philo);
	philo->lasteat = ft_currtime();
	ft_philo_sleep(philo, philo->data.tte);
	philo->eatcount++;
	sem_post(philo->forks);
	sem_post(philo->forks);
	ft_print_action("is sleeping", philo);
	ft_philo_sleep(philo, philo->data.tts);
	ft_print_action("is thinking", philo);
	return (1);
}

int	ft_philo_main(t_philo *philo)
{
	philo->lasteat = ft_currtime();
	while (ft_get_state(philo) == RUNNING)
	{
		if (ft_try_eat(philo) == -1 || ft_philo_check_death(philo))
		{
			ft_philo_die(philo);
			return (TERMINATE);
		}
		if (philo->data.mineat != 0 && philo->eatcount == philo->data.mineat)
		{
			ft_set_state(philo, DONE);
			return (DONE);
		}
	}
	return (RUNNING);
}
