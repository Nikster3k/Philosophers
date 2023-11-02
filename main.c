/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/02 16:28:42 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_print_data(t_lifedata data)
{
	printf("Number: %i\n", data.nbr);
	printf("Time to die: %i\n", data.ttd);
	printf("Time to eat: %i\n", data.tte);
	printf("Time to sleep: %i\n", data.tts);
	printf("Min amount of eat: %i\n", data.mineat);
}

void	ft_print_philos(t_philo *phil, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_print_data(phil[i].data);
		printf("thread id: %lu\n", phil[i].tid);
		printf("Fork1: %p | Fork2: %p\n", phil[i].fork1, phil[i].fork2);
		i++;
	}
}

void	ft_eat(t_philo *philo)
{
	struct timeval	tv;

	pthread_mutex_lock(philo->fork2);
	pthread_mutex_lock(philo->fork1);
	printf("%i Life left: %f\n", philo->data.nbr, philo->lifecount);
	if (philo->lifecount >= philo->data.ttd)
		return ;
	gettimeofday(&tv, NULL);
	printf("%lu %i is eating\n",
		(tv.tv_sec * 1000) + (tv.tv_usec / 1000), philo->data.nbr);
	usleep(philo->data.tte * 1000);
	philo->lifecount -= philo->data.tte;
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	gettimeofday(&tv, NULL);
	printf("%lu %i is sleeping\n",
		(tv.tv_sec * 1000) + (tv.tv_usec / 1000), philo->data.nbr);
	usleep(philo->data.tts * 1000);
	gettimeofday(&tv, NULL);
	printf("%lu %i is thinking\n",
		(tv.tv_sec * 1000) + (tv.tv_usec / 1000), philo->data.nbr);
}

void	*ft_philo_loop(void	*data)
{
	t_philo			*philo;
	float			timetook;
	struct timeval	start;
	struct timeval	end;

	philo = data;
	pthread_detach(philo->tid);
	printf("Philo %i - Hello\n", philo->data.nbr);
	while (philo->lifecount < philo->data.ttd)
	{
		gettimeofday(&start, NULL);
		ft_eat(philo);
		gettimeofday(&end, NULL);
		timetook = (((end.tv_sec - start.tv_sec) * 1000)
				+ ((end.tv_usec - start.tv_usec) / 1000));
		philo->lifecount += timetook;
		printf("Philo%d - Lifeleft:%f\n", philo->data.nbr, philo->lifecount);
	}
	printf("%lu %i died\n",
		(end.tv_sec * 1000) + (end.tv_usec / 1000), philo->data.nbr);
	pthread_exit(NULL);
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

int	main(int argc, char **argv)
{
	t_philo		*philophs;
	t_lifedata	data;
	int			count;

	if (argc < 5 || argc > 6)
		return (1);
	count = ft_init_data(argc, argv, &data);
	printf("Number of philos: %i\n", count);
	philophs = ft_calloc(sizeof(t_philo), count);
	if (philophs == NULL)
		return (MALLOC_FAIL);
	if (ft_init_philosophers(philophs, count, data))
		return (ft_destroy_philosophers(MALLOC_FAIL, philophs, count));
	//ft_print_philos(philophs, count);
	ft_start_philos(philophs, count);
	ft_wait_philos(philophs, count);
	return (ft_destroy_philosophers(SUCCESS, philophs, count));
}
