/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:20 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/04 19:23:31 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_lock(t_fork	*fork)
{
	int	out;

	out = pthread_mutex_lock(&fork->mutex);
	fork->is_locked = 1;
	return (out);
}

int	ft_unlock(t_fork *fork)
{
	int	out;

	fork->is_locked = 0;
	out = pthread_mutex_unlock(&fork->mutex);
	return (0);
}

int	ft_took_forks(t_philo *philo)
{
	// if (philo->right->is_locked)
	// 	return (0);
	ft_lock(&philo->own);
	printf("%lu %i has taken a fork\n", ft_gcts(philo->data->st), philo->nbr);
	ft_lock(philo->right);
	printf("%lu %i has taken a fork\n", ft_gcts(philo->data->st), philo->nbr);
	return (1);
}

int	ft_drop_forks(t_philo *philo)
{
	int	out;

	out = ft_unlock(&philo->own);
	return (ft_unlock(philo->right) || out);
}
