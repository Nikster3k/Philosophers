/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:14:32 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/24 15:28:50 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy_semaphores(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->print_sema);
	sem_close(philo->sim);
	return (EXIT_SUCCESS);
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

int	ft_start_philos(pid_t *pids, t_philo *philo, int count)
{
	pid_t	curr;
	int		i;

	i = 0;
	while (i < count)
	{
		curr = fork();
		if (curr == 0)
		{
			free(pids);
			philo->nbr = i + 1;
			printf("Philo %i says hello!\n", philo->nbr);
			ft_destroy_semaphores(philo);
			exit(1);
		}
		else if (curr)
		{
			pids[i] = curr;
		}
		else if (curr == -1)
			return (-1);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_init_semaphores(t_philo *philo, int count)
{
	philo->forks = sem_open(SEMAPHORE_FORKS, O_CREAT, 0644, count);
	if (philo->forks == SEM_FAILED)
		return (SEM_FAIL);
	philo->print_sema = sem_open(SEMAPHORE_PRINT, O_CREAT, 0644, 1);
	if (philo->print_sema == SEM_FAILED)
	{
		sem_close(philo->forks);
		return (SEM_FAIL);
	}
	philo->sim = sem_open(SEMAPHORE_KILLER, O_CREAT, 0644, count);
	if (philo->sim == SEM_FAILED)
	{
		sem_close(philo->forks);
		sem_close(philo->print_sema);
		return (SEM_FAIL);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_lifedata	data;
	pid_t		*pids;
	int			count;

	if (ft_check_args(argc, argv))
		return (BAD_ARGS);
	count = ft_init_data(argc, argv, &data);
	pids = ft_calloc(count, sizeof(pid_t));
	if (pids == NULL)
		return (MALLOC_FAIL);
	if (ft_init_semaphores(&philo, count))
	{
		free(pids);
		return (SEM_FAIL);
	}
	ft_start_philos(pids, &philo, count);
	free(pids);
	ft_destroy_semaphores(&philo);
	sem_unlink(SEMAPHORE_FORKS);
	sem_unlink(SEMAPHORE_PRINT);
	return (0);
}
