/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/08 16:49:20 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_lock(t_fork	*fork)
{
	int	out;

	out = pthread_mutex_lock(&fork->mutex);
	pthread_mutex_lock(&fork->bool_mutex);
	fork->is_locked = 1;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (out);
}

int	ft_unlock(t_fork *fork)
{
	int	out;

	pthread_mutex_lock(&fork->bool_mutex);
	fork->is_locked = 0;
	pthread_mutex_unlock(&fork->bool_mutex);
	out = pthread_mutex_unlock(&fork->mutex);
	return (out);
}

int	ft_fork_check(t_fork *fork)
{
	int	ret;

	pthread_mutex_lock(&fork->bool_mutex);
	ret = fork->is_locked;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (ret);
}

int	ft_get_fork_idx(t_fork *fork)
{
	int	idx;

	pthread_mutex_lock(&fork->bool_mutex);
	idx = fork->idx;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (idx);
}

int	ft_took_forks(t_philo *philo)
{
	if (ft_get_fork_idx(&philo->own) < ft_get_fork_idx(philo->right))
	{
		if (ft_fork_check(&philo->own))
			return (0);
		ft_lock(&philo->own);
		if (ft_fork_check(philo->right))
		{
			ft_unlock(&philo->own);
			return (0);
		}
		ft_print_multi("has taken own fork", philo);
		ft_lock(philo->right);
		ft_print_multi("has taken right fork", philo);
	}
	else
	{
		if (ft_fork_check(philo->right))
			return (0);
		ft_lock(philo->right);
		if (ft_fork_check(&philo->own))
		{
			ft_unlock(philo->right);
			return (0);
		}
		ft_print_multi("has taken right fork", philo);
		ft_lock(&philo->own);
		ft_print_multi("has taken own fork", philo);
	}
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	if (ft_get_fork_idx(&philo->own) < ft_get_fork_idx(philo->right))
	{
		ft_unlock(philo->right);
		ft_unlock(&philo->own);
	}
	else
	{
		ft_unlock(&philo->own);
		ft_unlock(philo->right);
	}
	return (1);
}
