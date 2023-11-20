/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:44:28 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/20 16:04:12 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_philo(t_philo *philo)
{
	if (philo->state == TERMINATE)
		return ;
	ft_print_action("died", philo, ft_gcts(philo->data.st));
	philo->state = TERMINATE;
	pthread_mutex_lock(&philo->term_mutex);
	*(philo->term_state) = TERMINATE;
	pthread_mutex_unlock(&philo->term_mutex);
}

int	ft_check_death(t_philo *philo)
{
	return (ft_currtime() - philo->lasteat >= philo->data.ttd);
}

void	ft_philo_sleep(t_philo *philo, int time_ms)
{
	long	sleep_time;

	sleep_time = ft_currtime() + time_ms;
	while (sleep_time >= ft_currtime() && philo->state == RUNNING)
	{
		if (ft_check_death(philo))
			ft_kill_philo(philo);
	}
}

int	ft_philo_action(t_philo *philo)
{
	if (ft_lock_forks(philo))
	{
		ft_print_action("is eating", philo, ft_gcts(philo->data.st));
		philo->lasteat = ft_currtime();
		ft_philo_sleep(philo, philo->data.tte);
		philo->eatcount++;
		if (philo->state == TERMINATE)
		{
			ft_unlock_forks(philo);
			return (-1);
		}
		ft_unlock_forks(philo);
		ft_print_action("is sleeping", philo, ft_gcts(philo->data.st));
		ft_philo_sleep(philo, philo->data.tts);
		if (philo->state == TERMINATE)
			return (-1);
		ft_print_action("is thinking", philo, ft_gcts(philo->data.st));
	}
	return (0);
}

void	*ft_philo_main(void *data)
{
	t_philo	*self;

	self = data;
	while (ft_sim_running(self) == STOP)
		;
	self->data.st = ft_currtime();
	self->lasteat = self->data.st;
	ft_print_action("is thinking", self, ft_gcts(self->data.st));
	while (self->state == RUNNING && ft_sim_running(self) == RUNNING)
	{
		if (ft_philo_action(self) == -1)
			break ;
		if (ft_currtime() - self->lasteat >= self->data.ttd)
			ft_kill_philo(self);
		if (self->data.mineat != 0 && self->eatcount == self->data.mineat)
			self->state = DONE;
	}
	return (NULL);
}
