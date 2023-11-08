/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:34 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/08 19:36:49 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_philo_state(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->term_mutex);
	ret = philo->state;
	pthread_mutex_unlock(&philo->term_mutex);
	return (ret);
}

void	ft_set_philo_state(t_philo *philo, int val)
{
	pthread_mutex_lock(&philo->term_mutex);
	philo->state = val;
	pthread_mutex_unlock(&philo->term_mutex);
}

long	ft_try_eat(t_philo *philo)
{
	if (ft_took_forks(philo))
	{
		if (ft_philo_check_death(philo))
			return (-1);
		ft_print_multi("is eating", philo);
		philo->lasteat = ft_currtime();
		ft_philo_wait(philo, philo->data.tte);
		philo->eatcount++;
		ft_drop_forks(philo);
		ft_print_multi("is sleeping", philo);
		ft_philo_wait(philo, philo->data.tts);
		ft_print_multi("is thinking", philo);
		return (1);
	}
	return (0);
}

void	*ft_philo_main(void *void_philo)
{
	t_philo	*philo;
	long	timetook;

	philo = void_philo;
	philo->lasteat = ft_currtime();
	if (philo->tid % 2)
		ft_philo_wait(philo, 10);
	while (ft_get_philo_state(philo) == RUNNING)
	{
		timetook = ft_try_eat(philo);
		if (timetook == -1 || ft_philo_check_death(philo))
		{
			ft_philo_die(philo);
			break ;
		}
		if (philo->data.mineat != 0 && philo->eatcount == philo->data.mineat)
		{
			ft_set_philo_state(philo, DONE);
			break ;
		}
	}
	ft_tryunlock(philo, philo->right);
	ft_tryunlock(philo, &philo->own);
	return (NULL);
}

int	ft_wait_philos(t_philo *philos, int count)
{
	int	i;
	int	x;
	int	done_count;

	i = 0;
	done_count = 0;
	while (done_count != count)
	{
		i *= (i < count);
		if (ft_get_philo_state(&philos[i]) == DONE)
			done_count++;
		if (ft_get_philo_state(&philos[i]) == TERMINATE)
		{
			x = 0;
			while (x < count)
				ft_set_philo_state(&philos[x++], TERMINATE);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < count)
		pthread_join(philos[i++].tid, NULL);
	return (EXIT_SUCCESS);
}
