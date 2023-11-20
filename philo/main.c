/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/20 18:20:40 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait_threads(t_philo *philos, int count)
{
	void	*ret;
	int		i;

	i = 0;
	while (i < count)
		pthread_join(philos[i++].tid, &ret);
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
	return (EXIT_SUCCESS);
}

int	ft_sim_running(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->term_mutex);
	ret = *(philo->term_state);
	pthread_mutex_unlock(&philo->term_mutex);
	return (ret);
}

void	ft_sim_set_state(t_philo *philo, t_state new_state)
{
	pthread_mutex_lock(&philo->term_mutex);
	*(philo->term_state) = new_state;
	pthread_mutex_unlock(&philo->term_mutex);
}

int	ft_start_philos(t_philo *philos, int count)
{
	long	start_time;
	int		i;

	i = 0;
	if (count == 1)
	{
		if (pthread_create(&philos[0].tid, NULL, ft_philo_solo, &philos[0]))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	start_time = ft_currtime();
	while (i < count)
	{
		philos[i].data.st = start_time;
		if (pthread_create(&philos[i].tid, NULL, ft_philo_main, &philos[i]))
		{
			ft_sim_set_state(&philos[0], TERMINATE);
			ft_wait_threads(philos, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philo		*philophs;
	t_state		sim_state;
	t_lifedata	data;
	int			count;

	if (ft_check_args(argc, argv))
		return (BAD_ARGS);
	count = ft_init_data(argc, argv, &data);
	philophs = ft_calloc(sizeof(t_philo), count);
	if (philophs == NULL)
		return (MALLOC_FAIL);
	sim_state = STOP;
	if (ft_init_philosophers(philophs, count, &data, &sim_state))
		return (ft_destroy_philosophers(MALLOC_FAIL, philophs, count));
	if (ft_start_philos(philophs, count))
		return (ft_destroy_philosophers(EXIT_FAILURE, philophs, count));
	pthread_mutex_lock(&philophs->term_mutex);
	sim_state = RUNNING;
	pthread_mutex_unlock(&philophs->term_mutex);
	ft_wait_threads(philophs, count);
	return (ft_destroy_philosophers(EXIT_SUCCESS, philophs, count));
}
