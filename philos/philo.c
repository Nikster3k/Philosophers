/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:34 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/06 13:20:37 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_terminate(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->term_mutex);
	ret = philo->terminate;
	pthread_mutex_unlock(&philo->term_mutex);
	return (ret);
}

void	ft_set_terminate(t_philo *philo)
{
	pthread_mutex_lock(&philo->term_mutex);
	philo->terminate = 1;
	pthread_mutex_unlock(&philo->term_mutex);
}

long	ft_eat(t_philo *philo)
{
	struct timeval	start;
	struct timeval	end;
	char			taken;

	gettimeofday(&start, NULL);
	taken = ft_took_forks(philo);
	if (taken == 1)
	{
		if (ft_tvtms(&start) - ft_currtime() + philo->lifecount
			>= philo->data.ttd)
			return (-1);
		ft_print_mutlti("is eating", ft_gcts(philo->data.st), philo->nbr);
		usleep(philo->data.tte * 1000);
		philo->eatcount++;
		philo->lifecount = -(philo->data.tte);
		ft_drop_forks(philo);
		ft_print_mutlti("is sleeping", ft_gcts(philo->data.st), philo->nbr);
		usleep(philo->data.tts * 1000);
		ft_print_mutlti("is thinking", ft_gcts(philo->data.st), philo->nbr);
	}
	else
		usleep(1);
	gettimeofday(&end, NULL);
	return (ft_tvtms(&end) - ft_tvtms(&start));
}

void	*ft_philo_main(void *void_philo)
{
	t_philo	*philo;
	long	timetook;

	philo = void_philo;
	while (!ft_get_terminate(philo))
	{
		if (philo->lifecount >= philo->data.ttd)
		{
			ft_print_mutlti("died", ft_gcts(philo->data.st), philo->nbr);
			ft_set_terminate(philo);
			break ;
		}
		timetook = ft_eat(philo);
		if (timetook == -1)
		{
			ft_print_mutlti("died", ft_gcts(philo->data.st), philo->nbr);
			break ;
		}
		if (philo->data.mineat != 0 && philo->eatcount == philo->data.mineat)
			break ;
		philo->lifecount += timetook;
	}
	ft_unlock(philo->right);
	ft_unlock(&philo->own);
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
		if (philos[i].data.mineat != 0
			&& philos[i].eatcount >= philos[i].data.mineat)
			done_count++;
		if (philos[i].terminate)
		{
			x = 0;
			while (x < count)
				ft_set_terminate(&philos[x++]);
			break ;
		}
		i++;
	}
	i = 0;
	while (i < count)
		pthread_join(philos[i++].tid, NULL);
	return (SUCCESS);
}
