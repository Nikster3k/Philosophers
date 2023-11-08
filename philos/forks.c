/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/08 19:42:07 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_trylock(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->bool_mutex);
	if (fork->owner == philo->tid)
		return (2);
	if (fork->owner != 0)
	{
		pthread_mutex_unlock(&fork->bool_mutex);
		return (0);
	}
	pthread_mutex_lock(&fork->mutex);
	fork->owner = philo->tid;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (1);
}

int	ft_tryunlock(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->bool_mutex);
	if (fork->owner != philo->tid)
	{
		pthread_mutex_unlock(&fork->bool_mutex);
		return (0);
	}
	pthread_mutex_unlock(&fork->mutex);
	fork->owner = 0;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (1);
}

int	ft_fork_check(t_philo *philo, t_fork *fork)
{
	int	ret;

	pthread_mutex_lock(&fork->bool_mutex);
	ret = fork->owner == philo->tid;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (ret);
}

int	ft_took_forks(t_philo *philo)
{
	if (!ft_trylock(philo, &philo->own))
		return (0);
	if (ft_philo_check_death(philo))
	{
		ft_philo_die(philo);
		return (0);
	}
	if (!ft_trylock(philo, philo->right))
	{
		ft_tryunlock(philo, &philo->own);
		return (0);
	}
	ft_print_multi("has taken a fork", philo);
	ft_print_multi("has taken a fork", philo);
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	ft_tryunlock(philo, philo->right);
	ft_tryunlock(philo, &philo->own);
	return (1);
}
