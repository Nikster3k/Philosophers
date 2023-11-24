/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:44:28 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/24 15:31:35 by nsassenb         ###   ########.fr       */
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

	sem_wait(philo->self);
	if (philo->state == DONE)
		is_dead = 0;
	else
		is_dead = ((ft_currtime() - philo->lasteat) >= philo->data.ttd)
			|| philo->state == TERMINATE;
	sem_post(philo->self);
	return (is_dead);
}

void	ft_philo_sleep(t_philo *philo, int time_ms)
{
	const int	check_ms = 60;

	while (time_ms > 0)
	{
		if (ft_check_death(philo))
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
		philo->lasteat = ft_currtime();
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

void	ft_philo_main(t_philo *self)
{
	ft_philo_eat(self);
	while (ft_get_philo_state(self) == RUNNING)
	{
		if (self->data.mineat != -1 && self->eatcount == self->data.mineat)
			self->state == DONE;
		if (ft_philo_action(self) == -1)
			break ;
	}
	return (NULL);
}
