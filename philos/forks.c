/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/05 20:21:56 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_lock(t_fork	*fork)
{
	int	out;

	out = pthread_mutex_lock(&fork->mutex);
	pthread_mutex_lock(&fork->check);
	fork->is_locked = 1;
	pthread_mutex_unlock(&fork->check);
	return (out);
}

int	ft_unlock(t_fork *fork)
{
	int	out;

	pthread_mutex_lock(&fork->check);
	fork->is_locked = 0;
	pthread_mutex_unlock(&fork->check);
	out = pthread_mutex_unlock(&fork->mutex);
	return (0);
}

int	ft_fork_check(t_fork *fork)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&fork->check);
	if (fork->is_locked)
		ret = 1;
	pthread_mutex_unlock(&fork->check);
	return (ret);
}

int	ft_took_forks(t_philo *philo)
{
	if (ft_fork_check(philo->right))
		return (0);
	ft_lock(&philo->own);
	ft_print_mutlti("has taken a fork", ft_gcts(philo->data.st), philo->nbr);
	ft_lock(philo->right);
	ft_print_mutlti("has taken a fork", ft_gcts(philo->data.st), philo->nbr);
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	int	out;

	out = ft_unlock(philo->right);
	return (ft_unlock(&philo->own) || out);
}
