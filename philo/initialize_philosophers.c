/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:12:52 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/23 15:41:19 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy_philosophers(int err, t_philo *phil, t_sim *sim, int count)
{
	int	i;

	if (phil == NULL)
		return (err);
	i = 0;
	pthread_mutex_destroy(&sim->sim_mutex);
	while (i < count)
	{
		pthread_mutex_destroy(&phil[i].own);
		pthread_mutex_destroy(&phil[i].data_mutex);
		i++;
	}
	free(phil);
	return (err);
}

int	ft_init_mutexes(t_philo *philos, t_sim *sim, int count)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&sim->sim_mutex, NULL))
		return (MUTEX_INITFAIL);
	while (i < count)
	{
		if (pthread_mutex_init(&philos[i].own, NULL))
			return (i);
		if (pthread_mutex_init(&philos[i].data_mutex, NULL))
		{
			pthread_mutex_destroy(&philos[i].own);
			return (i);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_init_philosophers(t_philo *philos, int count,
	t_lifedata *data, t_sim *sim)
{
	int		i;

	i = ft_init_mutexes(philos, sim, count);
	if (i)
		return (i);
	i = 0;
	while (i < count)
	{
		philos[i] = (t_philo){philos[i].tid, *data, i + 1, 0, ft_currtime(),
			philos[i].own, NULL, RUNNING, philos[i].data_mutex, sim};
		if (i != count - 1)
			philos[i].right = &philos[i + 1].own;
		i++;
	}
	philos[count - 1].right = &philos[0].own;
	return (EXIT_SUCCESS);
}

int	ft_init_data(int argc, char **argv, t_lifedata *data)
{
	int	count;

	count = ft_atol(argv[1]);
	data->ttd = ft_atol(argv[2]);
	data->tte = ft_atol(argv[3]);
	data->tts = ft_atol(argv[4]);
	if (argc == 6)
		data->mineat = ft_atol(argv[5]);
	else
		data->mineat = -1;
	return (count);
}
