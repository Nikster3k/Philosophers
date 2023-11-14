/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:12:52 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/08 19:13:55 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_philos(t_philo *philos, int count, t_lifedata data)
{
	sem_t	*status;
	sem_t	*forks;
	int		i;

	forks = sem_open(SEMA_NAME_FORKS, O_CREAT, 0644, count);
	if (forks == SEM_FAILED)
		return (SEMAPHORE_FAIL);
	status = sem_open(SEMA_NAME_STATUS, O_CREAT, 0644);
	if (status == SEM_FAILED)
		return (SEMAPHORE_FAIL);
	i = 0;
	while (i < count)
	{
		philos[i].data = data;
		philos[i].forks = forks;
		philos[i].status = status;
		philos[i].nbr = i + 1;
		philos[i].lasteat = ft_currtime();
		philos[i].eatcount = 0;
		philos[i].state = RUNNING;
		i++;
	}
	return (EXIT_SUCCESS);
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
	data->st = ft_currtime();
	return (count);
}
