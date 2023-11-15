/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/15 18:41:01 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_trylock(t_philo *philo, t_fork *fork)
{
	pthread_t	tid;

	tid = ft_get_owner(fork);
	if (tid == philo->tid)
		return (2);
	if (tid != 0)
		return (0);
	pthread_mutex_lock(&fork->mutex);
	ft_set_owner(fork, philo->tid);
	return (1);
}

int	ft_tryunlock(t_philo *philo, t_fork *fork)
{
	pthread_t	tid;

	tid = ft_get_owner(fork);
	if (tid != philo->tid)
		return (0);
	pthread_mutex_unlock(&fork->mutex);
	ft_set_owner(fork, 0);
	return (1);
}

int	ft_fork_check(t_philo *philo, t_fork *fork)
{
	return (ft_get_owner(fork) == philo->tid);
}

int	ft_took_forks(t_philo *philo)
{
	int	own;
	int	right;

	own = ft_trylock(philo, &philo->own);
	if (own)
	{
		right = ft_trylock(philo, philo->right);
		if (right)
		{
			if (own == 1)
				ft_print_action("has taken a fork", philo);
			if (right == 1)
				ft_print_action("has taken a fork", philo);
			return (1);
		}
		ft_tryunlock(philo, &philo->own);
	}
	return (0);
}

int	ft_drop_forks(t_philo *philo)
{
	ft_tryunlock(philo, philo->right);
	ft_tryunlock(philo, &philo->own);
	return (1);
}
