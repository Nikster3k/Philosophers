/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/04 16:23:59 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

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
	ft_print_data(*phil[0].data);
	while (i < count)
	{
		printf("Number: %i | thread id: %lu\n", phil[i].nbr, phil[i].tid);
		printf("Fork1: %p | Fork2: %p\n",
			&phil[i].own.mutex, &phil[i].right->mutex);
		i++;
	}
}

void	ft_eat(t_philo *philo)
{
	struct timeval	tv;

	philo->own.is_locked = 1;
	printf("%i Life spent: %i\n", philo->nbr, philo->lifecount);
	if (philo->lifecount >= philo->data->ttd)
		return ;
	gettimeofday(&tv, NULL);
	printf("%lu %i is eating\n",
		(tv.tv_sec * 1000) + (tv.tv_usec / 1000), philo->nbr);
	philo->eatcount++;
	usleep(philo->data->tte * 1000);
	philo->lifecount = -(philo->data->tte);
}

void	ft_check_forks(t_philo *philo)
{
	struct timeval	tv;

	if (philo->right->is_locked)
		return ;
	if (pthread_mutex_lock(&philo->right->mutex))
		printf("Failed lock?\n");
	philo->right->is_locked = 1;
	if (philo->own.is_locked)
	{
		pthread_mutex_unlock(&philo->right->mutex);
		philo->right->is_locked = 0;
		return ;
	}
	pthread_mutex_lock(&philo->own.mutex);
	ft_eat(philo);
	pthread_mutex_unlock(&philo->right->mutex);
	philo->right->is_locked = 0;
	pthread_mutex_unlock(&philo->own.mutex);
	philo->own.is_locked = 0;
	gettimeofday(&tv, NULL);
	printf("%lu %i is sleeping\n",
		(tv.tv_sec * 1000) + (tv.tv_usec / 1000), philo->nbr);
	usleep(philo->data->tts * 1000);
	gettimeofday(&tv, NULL);
	printf("%lu %i is thinking\n",
		(tv.tv_sec * 1000) + (tv.tv_usec / 1000), philo->nbr);
}

void	*ft_philo_loop(void	*data)
{
	t_philo			*philo;
	float			timetook;
	struct timeval	start;
	struct timeval	end;

	philo = data;
	while (philo->lifecount < philo->data->ttd)
	{
		gettimeofday(&start, NULL);
		ft_check_forks(philo);
		gettimeofday(&end, NULL);
		timetook = (((end.tv_sec - start.tv_sec) * 1000)
				+ ((end.tv_usec - start.tv_usec) / 1000));
		if (philo->data->mineat != 0 && philo->data->mineat == philo->eatcount)
			pthread_exit(NULL);
		philo->lifecount += timetook;
		//printf("Philo%d - Lifespent:%i\n", philo->nbr, philo->lifecount);
	}
	printf("%lu %i died\n",
		(end.tv_sec * 1000) + (end.tv_usec / 1000), philo->nbr);
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

int	ft_wait_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
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
	if (ft_init_philosophers(philophs, count, &data))
		return (ft_destroy_philosophers(MALLOC_FAIL, philophs, count));
	ft_print_philos(philophs, count);
	ft_start_philos(philophs, count);
	ft_wait_philos(philophs, count);
	return (ft_destroy_philosophers(SUCCESS, philophs, count));
}
