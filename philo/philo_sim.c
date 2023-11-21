/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:53:06 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/21 19:27:53 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_wait_threads(t_philo *philos, int count)
{
	void	*ret;
	int		i;

	i = 0;
	while (i < count)
		pthread_join(philos[i++].tid, &ret);
}

int	ft_sim_get_state(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->sim->sim_mutex);
	ret = philo->sim->state;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
	return (ret);
}

void	ft_sim_set_state(t_philo *philo, t_state new_state)
{
	pthread_mutex_lock(&philo->sim->sim_mutex);
	philo->sim->state = new_state;
	pthread_mutex_unlock(&philo->sim->sim_mutex);
}

int	ft_wait_philos(t_philo *philos, int count)
{
	int	x;
	int	done_count;

	done_count = 0;
	while (done_count != count)
	{
		x = -1;
		done_count = 0;
		while (++x < count)
		{
			if (ft_get_philo_state(&philos[x]) == DONE)
				done_count++;
			if (ft_check_death(&philos[x]))
			{
				ft_kill_philo(&philos[x]);
				x = 0;
				while (x < count)
					ft_set_philo_state(&philos[x++], TERMINATE);
				done_count = count;
				break ;
			}
		}
	}
	ft_wait_threads(philos, count);
	return (EXIT_SUCCESS);
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
