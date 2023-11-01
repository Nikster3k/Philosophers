/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/01 15:04:09 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_destroy_philosophers(t_philo *phil, int count)
{
	if (phil == NULL)
		return ;
	while (count--)
	{
		if (phil[count].fork1 != NULL)
		{
			pthread_mutex_destroy(phil[count].fork1);
			free(phil[count].fork1);
		}
		if (phil[count].fork2 != NULL)
		{
			pthread_mutex_destroy(phil[count].fork1);
			free(phil[count].fork2);
		}
	}
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
		philos[i].fork1 = calloc(sizeof(pthread_mutex_t), 1);
		philos[i].fork2 = calloc(sizeof(pthread_mutex_t), 1);
		if (philos[i].fork2 == NULL || philos[i].fork1 == NULL)
			return (1);
		if (pthread_mutex_init(philos[i].fork2, NULL))
			return (2);
		if (i != 0)
			philos[i].fork1 = philos[i - 1].fork2;
		i++;
	}
	philos[0].fork1 = philos[count - 1].fork2;
	return (0);
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
	return (count);
}

void	ft_print_data(t_lifedata data)
{
	printf("Number: %i\n", data.nbr);
	printf("Time to die: %i\n", data.ttd);
	printf("Time to eat: %i\n", data.tte);
	printf("Time to sleep: %i\n", data.tts);
	printf("Min amount of eat: %i\n", data.mineat);
}

void	ft_print_philo(t_philo *phil)
{
	ft_print_data(phil->data);
	printf("thread id: %lu\n", phil->tid);
	printf("Fork1: %p | Fork2: %p\n", phil->fork1, phil->fork2);
}

int	main(int argc, char **argv)
{
	t_philo		*philophs;
	t_lifedata	data;
	int			count;

	if (argc < 5)
		return (1);
	count = ft_init_data(argc, argv, &data);
	printf("Number of philos: %i\n", count);
	philophs = ft_calloc(sizeof(t_philo), count);
	if (philophs == NULL)
		return (0);
	if (ft_init_philosophers(philophs, count, data))
		ft_destroy_philosophers(philophs, count);
	while (count--)
	{
		ft_print_philo(&philophs[count]);
	}
	free(philophs);
}
