/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/16 16:53:54 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait_threads(t_philo *philos, int count)
{
	void	*ret;
	int		i;

	i = 0;
	while (i < count)
	{
		// printf("Philo %i state: %i\n", philos[i].nbr, ft_get_philo_state(&philos[i]));
		pthread_join(philos[i].tid, &ret);
		// printf("Philo %i returned: %p\n", philos[i].nbr, ret);
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
	return (EXIT_SUCCESS);
}

int	ft_start_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	if (count == 1)
	{
		pthread_create(&philos[0].tid, NULL, ft_philo_solo, &philos[0]);
		return (EXIT_SUCCESS);
	}
	while (i < count)
	{
		pthread_create(&philos[i].tid, NULL, ft_philo_main, &philos[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philo		*philophs;
	t_lifedata	data;
	int			count;

	if (ft_check_args(argc, argv))
		return (BAD_ARGS);
	count = ft_init_data(argc, argv, &data);
	philophs = ft_calloc(sizeof(t_philo), count);
	if (philophs == NULL)
		return (MALLOC_FAIL);
	data.st = ft_currtime();
	if (ft_init_philosophers(philophs, count, &data))
		return (ft_destroy_philosophers(MALLOC_FAIL, philophs, count));
	ft_start_philos(philophs, count);
	ft_kill_cascade(philophs, count);
	ft_wait_threads(philophs, count);
	return (ft_destroy_philosophers(EXIT_SUCCESS, philophs, count));
}
