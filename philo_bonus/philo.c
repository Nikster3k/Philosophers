/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:34 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/17 18:01:35 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_try_take_fork(t_philo *philo)
{
	while (philo->forks->__align <= 0)
		ft_philo_sleep(philo, 1);
	if (philo->state == TERMINATE)
		return (-1);
	sem_wait(philo->forks);
	return (1);
}

int	ft_take_forks(t_philo *philo)
{
	if (ft_try_take_fork(philo) == -1)
		return (-1);
	ft_print_action("has taken a fork", philo);
	if (ft_philo_check_death(philo))
	{
		sem_post(philo->forks);
		ft_philo_die(philo);
		return (-1);
	}
	if (ft_try_take_fork(philo) == -1)
	{
		sem_post(philo->forks);
		return (-1);
	}
	ft_print_action("has taken a fork", philo);
	if (ft_philo_check_death(philo))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		ft_philo_die(philo);
		return (-1);
	}
	return (1);
}

int	ft_try_eat(t_philo *philo)
{
	int	out;

	out = ft_take_forks(philo);
	if (out == 1)
	{
		ft_print_action("is eating", philo);
		philo->lasteat = ft_currtime();
		ft_philo_sleep(philo, philo->data.tte);
		philo->eatcount++;
		sem_post(philo->forks);
		sem_post(philo->forks);
		ft_print_action("is sleeping", philo);
		ft_philo_sleep(philo, philo->data.tts);
	}
	return (out);
}

int	ft_philo_main(t_philo *philo)
{
	philo->lasteat = ft_currtime();
	while (philo->state == RUNNING)
	{
		ft_print_action("is thinking", philo);
		if (ft_try_eat(philo) == -1 || ft_philo_check_death(philo))
		{
			ft_philo_die(philo);
			return (TERMINATE);
		}
		if (philo->data.mineat != 0 && philo->eatcount == philo->data.mineat)
		{
			philo->state = DONE;
			return (DONE);
		}
	}
	return (RUNNING);
}

void	ft_wait_philos(pid_t first, int count)
{
	int	i;
	int	ret;

	i = 0;
	while (i < count)
	{
		waitpid(0, &ret, 0);
		if (WEXITSTATUS(ret) == 2)
			ft_kill_philos(first, count);
		i++;
	}
}
