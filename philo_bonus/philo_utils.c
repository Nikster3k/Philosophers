/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:02:59 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/24 15:31:09 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_eat(t_philo *philo)
{
	sem_wait(philo->self);
	philo->lasteat = ft_currtime();
	sem_post(philo->self);
}

int	ft_get_philo_state(t_philo *philo)
{
	int	ret;

	sem_wait(philo->self);
	ret = philo->state;
	sem_post(philo->self);
	return (ret);
}

void	ft_set_philo_state(t_philo *philo, int val)
{
	sem_wait(philo->self);
	philo->state = val;
	sem_post(philo->self);
}

int	ft_lock_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	ft_print_action("has taken a fork", philo);
	sem_wait(philo->forks);
	ft_print_action("has taken a fork", philo);
	return (EXIT_SUCCESS);
}

void	ft_unlock_forks(t_philo *philo)
{
	sem_post(philo->forks);
	sem_post(philo->forks);
}
