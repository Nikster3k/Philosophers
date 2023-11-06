/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/06 13:18:21 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_data(t_lifedata data)
{
	printf("Time to die: %i\n", data.ttd);
	printf("Time to eat: %i\n", data.tte);
	printf("Time to sleep: %i\n", data.tts);
	printf("Min amount of eat: %i\n", data.mineat);
}

void	ft_print_philos(t_philo *phil, int count)
{
	int	i;

	i = 0;
	ft_print_data(phil[0].data);
	while (i < count)
	{
		printf("Number: %i | thread id: %lu\n", phil[i].nbr, phil[i].tid);
		printf("Own: %p | Right: %p\n",
			&phil[i].own.mutex, &phil[i].right->mutex);
		i++;
	}
}

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	x;

	if (argc < 5 || argc > 6)
		return (BAD_ARGS);
	i = 1;
	while (i < argc)
	{
		x = 0;
		while (argv[i][x])
			if (!ft_isdigit(argv[i][x++]))
				return (BAD_ARGS);
		i++;
	}
	return (SUCCESS);
}

int	ft_start_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_create(&philos[i].tid, NULL, ft_philo_main, &philos[i]);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philo		*philophs;
	t_lifedata	data;
	int			count;

	if (ft_check_args(argc, argv))
		return (BAD_ARGS);
	count = ft_init_data(argc, argv, &data);
	printf("Number of philos: %i\n", count);
	philophs = ft_calloc(sizeof(t_philo), count);
	if (philophs == NULL)
		return (MALLOC_FAIL);
	data.st = ft_currtime();
	if (ft_init_philosophers(philophs, count, &data))
		return (ft_destroy_philosophers(MALLOC_FAIL, philophs, count));
	ft_print_philos(philophs, count);
	ft_start_philos(philophs, count);
	ft_wait_philos(philophs, count);
	return (ft_destroy_philosophers(SUCCESS, philophs, count));
}
