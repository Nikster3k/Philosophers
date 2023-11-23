/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/23 17:33:21 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait_threads(t_philo *philos, int count)
{
	int		i;

	i = 0;
	while (i < count)
		pthread_join(philos[i++].tid, NULL);
}

static int	ft_check_args(int argc, char **argv)
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
	return (EXIT_SUCCESS);
}

static int	ft_start_philos(t_philo *philos, int count)
{
	long	start_time;
	int		i;

	i = 0;
	start_time = ft_currtime();
	if (count == 1)
	{
		philos[0].data.st = start_time;
		if (pthread_create(&philos[0].tid, NULL, ft_philo_solo, &philos[0]))
			return (FAIL_THREAD);
		return (EXIT_SUCCESS);
	}
	while (i < count)
	{
		philos[i].data.st = start_time;
		if (pthread_create(&philos[i].tid, NULL, ft_philo_main, &philos[i]))
		{
			ft_sim_set_state(&philos[0], TERMINATE);
			ft_philos_set_state(philos, i, TERMINATE);
			ft_wait_threads(philos, i);
			return (FAIL_THREAD);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philo		*philophs;
	t_sim		sim;
	t_lifedata	data;
	int			count;
	int			init_ret;

	if (ft_check_args(argc, argv))
		return (BAD_ARGS);
	count = ft_init_data(argc, argv, &data);
	philophs = ft_calloc(sizeof(t_philo), count);
	if (philophs == NULL)
		return (MALLOC_FAIL);
	sim.state = RUNNING;
	init_ret = ft_init_philosophers(philophs, count, &data, &sim);
	if (init_ret)
		return (ft_destroy_philosophers(MALLOC_FAIL, philophs, &sim, init_ret));
	if (ft_start_philos(philophs, count))
		return (ft_destroy_philosophers(FAIL_THREAD, philophs, &sim, count));
	ft_wait_philos(philophs, count);
	return (ft_destroy_philosophers(EXIT_SUCCESS, philophs, &sim, count));
}
