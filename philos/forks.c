/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/07 19:27:21 by nsassenb         ###   ########.fr       */
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

	if (pthread_mutex_lock(&fork->bool_mutex))
		return (-1);
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
		ft_lock(&philo->own);
		ft_print_multi("has taken a fork", philo);
		ft_lock(philo->right);
		ft_print_multi("has taken a fork", philo);
	}
	else
	{
		ft_lock(philo->right);
		ft_print_multi("has taken a fork", philo);
		ft_lock(&philo->own);
		ft_print_multi("has taken a fork", philo);
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
