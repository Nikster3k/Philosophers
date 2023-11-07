/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/07 12:26:49 by nsassenb         ###   ########.fr       */
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

int	ft_took_forks(t_philo *philo)
{
	if (ft_fork_check(philo->right) || ft_fork_check(&philo->own))
		return (0);
	ft_lock(&philo->own);
	ft_print_mutlti("has taken a fork", ft_gcts(philo->data.st), philo->nbr);
	ft_lock(philo->right);
	ft_print_mutlti("has taken a fork", ft_gcts(philo->data.st), philo->nbr);
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	return (ft_unlock(&philo->own) || ft_unlock(philo->right));
}
