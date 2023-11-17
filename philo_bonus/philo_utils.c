/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:34:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/17 14:37:49 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_philo_check_death(t_philo *philo)
{
	return (ft_currtime() - philo->lasteat >= philo->data.ttd);
}

void	ft_philo_die(t_philo *philo)
{
	if (philo->state != RUNNING)
		return ;
	ft_print_action("died", philo);
	philo->state = TERMINATE;
}

void	ft_philo_sleep(t_philo *philo, int sleep_ms)
{
	long	max_sleep;

	max_sleep = ft_currtime() + sleep_ms;
	while (max_sleep >= ft_currtime() && philo->state != TERMINATE)
	{
		usleep(100);
		if (ft_philo_check_death(philo))
		{
			ft_philo_die(philo);
			return ;
		}
	}
}

void	ft_kill_philos(pid_t first, int count)
{
	static char	s_run_count = 0;
	int			i;

	if (s_run_count > 0)
		return ;
	i = 0;
	while (i < count)
		kill(first + (i++), SIGKILL);
	s_run_count++;
}
