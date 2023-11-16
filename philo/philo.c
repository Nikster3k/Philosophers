/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:34 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/16 16:53:24 by nsassenb         ###   ########.fr       */
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

int	ft_try_eat(t_philo *philo)
{
	if (ft_took_forks(philo))
	{
		if (ft_philo_check_death(philo))
		{
			ft_drop_forks(philo);
			return (-1);
		}
		ft_print_action("is eating", philo);
		philo->lasteat = ft_currtime();
		usleep(philo->data.tte * 1000);
		philo->eatcount++;
		ft_drop_forks(philo);
		ft_print_action("is sleeping", philo);
		ft_philo_sleep(philo, philo->data.tts);
		ft_print_action("is thinking", philo);
		return (1);
	}
	return (0);
}

void	*ft_philo_main(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	philo->lasteat = ft_currtime();
	ft_print_action("is thinking", philo);
	while (ft_get_philo_state(philo) == RUNNING)
	{
		if (ft_try_eat(philo) == -1 || ft_philo_check_death(philo))
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
	ft_drop_forks(philo);
	return ((void *)(size_t)ft_get_philo_state(philo));
}

int	ft_kill_cascade(t_philo *philos, int count)
{
	int	i;
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
			i = 0;
			while (i < count)
				ft_set_philo_state(&philos[i++], DONE);
			break ;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
