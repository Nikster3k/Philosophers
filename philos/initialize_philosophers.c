/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:12:52 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/06 13:14:43 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy_philosophers(int err, t_philo *phil, int count)
{
	int	i;

	if (phil == NULL)
		return (err);
	i = 0;
	while (i < count)
		pthread_mutex_destroy(&phil[i++].own.mutex);
	free(phil);
	return (err);
}

int	ft_init_philosophers(t_philo *philos, int count, t_lifedata *data)
{
	int		i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&philos[i].own.mutex, NULL)
			|| pthread_mutex_init(&philos[i].own.bool_mutex, NULL)
			|| pthread_mutex_init(&philos[i].term_mutex, NULL))
			return (MUTEX_INITFAIL);
		i++;
	}
	i = 0;
	while (i < count)
	{
		philos[i].data = *data;
		philos[i].nbr = i + 1;
		philos[i].lifecount = 0;
		philos[i].eatcount = 0;
		philos[i].terminate = 0;
		if (i != count - 1)
			philos[i].right = &philos[i + 1].own;
		i++;
	}
	philos[count - 1].right = &philos[0].own;
	return (SUCCESS);
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
		data->mineat = 0;
	return (count);
}
