/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:02:59 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/20 00:18:14 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fork_unlock(t_philo *philo, t_fork *fork)
{
	if (ft_get_fork_owner(fork) != philo->tid)
		return (0);
	ft_set_fork_owner(fork, 0);
	pthread_mutex_unlock(&fork->mutex);
	return (1);
}

int	ft_fork_lock(t_philo *philo, t_fork *fork)
{
	if (ft_get_fork_owner(fork) == philo->tid)
		return (2);
	while (ft_set_fork_owner(fork, philo->tid) != 1)
	{
		if (ft_check_death(philo))
		{
			ft_kill_philo(philo);
			return (0);
		}
	}
	ft_set_fork_owner(fork, philo->tid);
	pthread_mutex_lock(&fork->mutex);
	return (1);
}

int	ft_lock_forks(t_philo *philo)
{
	int	fork1;
	int	fork2;

	if (philo->nbr == 1)
	{
		fork1 = ft_fork_lock(philo, philo->right);
		ft_print_action("has taken a fork", philo, ft_gcts(philo->data.st));
		if (fork1 == 0)
			return (0);
		fork2 = ft_fork_lock(philo, &philo->own);
		ft_print_action("has taken a fork", philo, ft_gcts(philo->data.st));
		if (fork2 == 0)
			ft_fork_unlock(philo, philo->right);
		return (fork1 && fork2);
	}
	fork1 = ft_fork_lock(philo, &philo->own);
	ft_print_action("has taken a fork", philo, ft_gcts(philo->data.st));
	if (fork1 == 0)
		return (0);
	fork2 = ft_fork_lock(philo, philo->right);
	ft_print_action("has taken a fork", philo, ft_gcts(philo->data.st));
	if (fork2 == 0)
		ft_fork_unlock(philo, philo->right);
	return (fork1 && fork2);
	return (fork1 && fork2);
}

void	ft_unlock_forks(t_philo *philo)
{
	if (philo->nbr == 1)
	{
		ft_fork_unlock(philo, &philo->own);
		ft_fork_unlock(philo, philo->right);
		return ;
	}
	ft_fork_unlock(philo, philo->right);
	ft_fork_unlock(philo, &philo->own);
}

void	*ft_philo_solo(void *data)
{
	t_philo	*self;

	self = data;
	self->lasteat = ft_currtime();
	ft_philo_sleep(self, self->data.ttd);
	ft_kill_philo(self);
	return (NULL);
}
