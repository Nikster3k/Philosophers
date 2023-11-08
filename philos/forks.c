/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/08 19:30:01 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_lock(t_fork	*fork)
{
	int	out;

	out = pthread_mutex_lock(&fork->mutex);
	pthread_mutex_lock(&fork->bool_mutex);
	fork->owner = 1;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (out);
}

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

int	ft_unlock(t_fork *fork)
{
	int	out;

	pthread_mutex_lock(&fork->bool_mutex);
	fork->owner = 0;
	pthread_mutex_unlock(&fork->bool_mutex);
	out = pthread_mutex_unlock(&fork->mutex);
	return (out);
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

int	ft_fork_check(t_fork *fork)
{
	int	ret;

	pthread_mutex_lock(&fork->bool_mutex);
	ret = fork->owner;
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
		ft_unlock(&philo->own);
		return (0);
	}
	ft_print_multi("has taken own fork", philo);
	ft_print_multi("has taken right fork", philo);
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	ft_unlock(philo->right);
	ft_unlock(&philo->own);
	return (1);
}
