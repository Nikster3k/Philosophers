/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:02:59 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/21 17:53:24 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_philo_state(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->data_mutex);
	ret = philo->state;
	pthread_mutex_unlock(&philo->data_mutex);
	return (ret);
}

void	ft_set_philo_state(t_philo *philo, int val)
{
	pthread_mutex_lock(&philo->data_mutex);
	philo->state = val;
	pthread_mutex_unlock(&philo->data_mutex);
}

int	ft_lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->own);
	if (ft_get_philo_state(philo) != RUNNING)
	{
		pthread_mutex_unlock(&philo->own);
		return (0);
	}
	ft_print_action("has taken a fork", philo);
	pthread_mutex_lock(philo->right);
	if (ft_get_philo_state(philo) != RUNNING)
	{
		pthread_mutex_unlock(&philo->own);
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	ft_print_action("has taken a fork", philo);
	return (1);
}

void	ft_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(&philo->own);
}
