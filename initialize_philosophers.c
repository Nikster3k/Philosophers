/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:12:52 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/02 15:35:47 by nsassenb         ###   ########.fr       */
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
	{
		if (phil[i].fork2 != NULL)
		{
			pthread_mutex_destroy(phil[i].fork2);
			free(phil[i].fork2);
		}
		i++;
	}
	free(phil);
	return (err);
}

//could stop initializing philosophers when encounter error and
//meanwhile count. Then use that count to also destroy the philos
//that way I know that when error 1 occured it was malloc fail.
//and error 2 I know that the mutex init failed and I dont have
//to destroy the mutex, which could maybe cause errors when it has
//not been initialized.

int	ft_init_philosophers(t_philo *philos, int count, t_lifedata data)
{
	int		i;

	i = 0;
	while (i < count)
	{
		philos[i].data = data;
		philos[i].data.nbr = i + 1;
		philos[i].lifecount = 0;
		philos[i].fork2 = ft_calloc(sizeof(pthread_mutex_t), 1);
		if (philos[i].fork2 == NULL)
			return (MALLOC_FAIL);
		if (pthread_mutex_init(philos[i].fork2, NULL))
			return (MUTEX_INITFAIL);
		if (i != 0)
			philos[i].fork1 = philos[i - 1].fork2;
		i++;
	}
	philos[0].fork1 = philos[count - 1].fork2;
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