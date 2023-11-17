/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:51:52 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/17 17:59:29 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_init_philo(t_philo *philo, int idx)
{
	philo->nbr = idx + 1;
	philo->eatcount = 0;
	philo->state = RUNNING;
}

pid_t	ft_start_philos(t_philo *philo, int count)
{
	pid_t	curr;
	pid_t	first;
	int		i;

	i = 0;
	while (i < count)
	{
		ft_init_philo(philo, i);
		curr = fork();
		philo->data.st = ft_currtime();
		if (curr == 0)
		{
			first = ft_philo_main(philo);
			sem_close(philo->forks);
			exit(first);
		}
		else if (curr && i == 0)
			first = curr;
		else if (curr == -1)
		{
			ft_kill_philos(first, i);
			break ;
		}
		i++;
	}
	return (first);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_lifedata	data;
	int			count;
	pid_t		first;

	if (ft_check_args(argc, argv))
		return (BAD_ARGS);
	count = ft_init_data(argc, argv, &data);
	philo.data = data;
	philo.forks = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, count);
	if (philo.forks == SEM_FAILED)
		return (SEMAPHORE_FAIL);
	first = ft_start_philos(&philo, count);
	ft_wait_philos(first, count);
	sem_close(philo.forks);
	sem_unlink(SEMAPHORE_NAME);
	return (0);
}
