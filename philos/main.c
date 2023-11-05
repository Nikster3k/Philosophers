/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/05 20:22:38 by nsassenb         ###   ########.fr       */
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

long	ft_do_it(t_philo *philo)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	if (ft_took_forks(philo))
	{
		if ((int)(philo->lifecount + (ft_currtime() - ft_tvtms(&start)))
			> philo->data.ttd)
			return (-1);
		ft_print_mutlti("is eating", ft_gcts(philo->data.st), philo->nbr);
		usleep(philo->data.tte * 1000);
		philo->lifecount = -(philo->data.tte);
		philo->eatcount++;
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

void	*ft_philo_loop(void	*data)
{
	t_philo			*philo;
	long			timetook;

	philo = data;
	while (philo->lifecount < philo->data.ttd)
	{
		pthread_mutex_lock(&philo->term_mutex);
		if (philo->terminate)
		{
			pthread_mutex_unlock(&philo->term_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->term_mutex);
		timetook = ft_do_it(philo);
		if (timetook == -1)
			break ;
		if (timetook == -2)
			return (NULL);
		if (philo->data.mineat != 0 && philo->data.mineat == philo->eatcount)
			return (NULL);
		philo->lifecount += timetook;
		//printf("Philo%d - Lifecount:%ld\n", philo->nbr, philo->lifecount);
	}
	ft_print_mutlti("died", ft_gcts(philo->data.st), philo->nbr);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->own.mutex);
	return (NULL);
}

int	ft_start_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_create(&philos[i].tid, NULL, ft_philo_loop, &philos[i]);
		i++;
	}
	return (SUCCESS);
}

void	ft_terminate_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->term_mutex);
	philo->terminate = 1;
	pthread_mutex_unlock(&philo->term_mutex);
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
		if (i >= count)
			i = 0;
		if (philos[i].data.mineat != 0
			&& philos[i].eatcount >= philos[i].data.mineat)
			done_count++;
		if (philos[i].lifecount >= philos[i].data.ttd)
		{
			printf("TERMINATE!\n");
			x = 0;
			while (x < count)
				ft_terminate_philo(&philos[x++]);
			break ;
		}
		i++;
	}
	while (i < count)
		pthread_join(philos[i++].tid, NULL);
	return (SUCCESS);
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
