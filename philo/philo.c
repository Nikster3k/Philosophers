/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:44:28 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/23 14:32:11 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_philo(t_philo *philo)
{
	if (ft_get_philo_state(philo) == TERMINATE)
		return ;
	ft_print_action("died", philo);
	ft_set_philo_state(philo, TERMINATE);
	ft_sim_set_state(philo, TERMINATE);
}

int	ft_check_death(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(&philo->data_mutex);
	if (philo->state == DONE)
		is_dead = 0;
	else
		is_dead = ((ft_currtime() - philo->lasteat) >= philo->data.ttd)
			|| philo->state == TERMINATE;
	pthread_mutex_unlock(&philo->data_mutex);
	return (is_dead);
}

void	ft_philo_sleep(t_philo *philo, int time_ms)
{
	const int	check_ms = 60;

	while (time_ms > 0)
	{
		if (ft_get_philo_state(philo) != RUNNING)
			break ;
		if (time_ms < check_ms)
			usleep((time_ms % check_ms) * 1000);
		else
			usleep(check_ms * 1000);
		time_ms -= check_ms;
	}
}

int	ft_philo_action(t_philo *philo)
{
	if (ft_lock_forks(philo))
	{
		pthread_mutex_lock(&philo->data_mutex);
		philo->lasteat = ft_currtime();
		pthread_mutex_unlock(&philo->data_mutex);
		ft_print_action("is eating", philo);
		ft_philo_sleep(philo, philo->data.tte);
		philo->eatcount++;
		ft_unlock_forks(philo);
		ft_print_action("is sleeping", philo);
		ft_philo_sleep(philo, philo->data.tts);
		ft_print_action("is thinking", philo);
	}
	return (0);
}

void	*ft_philo_main(void *data)
{
	t_philo	*self;

	self = data;
	if (ft_sim_get_state(self) == TERMINATE)
		return (NULL);
	if (self->nbr % 2 == 0)
		ft_philo_sleep(self, self->data.tte - 10);
	while (ft_get_philo_state(self) == RUNNING)
	{
		if (self->data.mineat != -1 && self->eatcount == self->data.mineat)
			ft_set_philo_state(self, DONE);
		if (ft_philo_action(self) == -1)
			break ;
		if (ft_sim_get_state(self) != RUNNING)
			break ;
	}
	return (NULL);
}
