/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:51:52 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/13 00:08:43 by nsassenb         ###   ########.fr       */
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

void	ft_kill_all(t_philo *philos, int count, int ret)
{
	int	i;

	if (WEXITSTATUS(ret) != 2)
		return ;
	printf("Kill all!\n");
	i = 0;
	while (i < count)
	{
		ft_set_state(&philos[i], TERMINATE);
		printf("Killed: %i\n", philos[i].nbr);
		i++;
	}
}

int	ft_start_processes(t_philo *philo, int count)
{
	pid_t	temp;
	int		i;

	i = 0;
	while (i < count)
	{
		temp = fork();
		if (temp == 0)
		{
			int	ecode;

			ecode = ft_philo_main(&philo[i]);
			return (ecode);
		}
		else if (temp == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_wait_for_process(t_philo *philos, int count)
{
	int		i;
	int		ret;
	pid_t	returnee;

	i = 0;
	returnee = 0;
	while (i < count)
	{
		returnee = waitpid(0, &ret, 0);
		printf("%i has Exit ret=%i\n", returnee, WEXITSTATUS(ret));
		if (WEXITSTATUS(ret) == 2)
			ft_kill_all(philos, count, ret);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_destoy_semaphores(t_philo *philos)
{
	sem_close(philos->status);
	sem_close(philos->forks);
	sem_unlink(SEMA_NAME_FORKS);
	sem_unlink(SEMA_NAME_STATUS);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_lifedata	data;
	int			count;
	int			ret;

	if (ft_check_args(argc, argv))
		return (BAD_ARGS);
	count = ft_init_data(argc, argv, &data);
	philos = ft_calloc(count, sizeof(t_philo));
	if (philos == NULL)
		return (MALLOC_FAIL);
	if (ft_init_philos(philos, count, data))
	{
		ft_destoy_semaphores(philos);
		free(philos);
		return (SEMAPHORE_FAIL);
	}
	ret = ft_start_processes(philos, count);
	if (ret > 0)
		return (ret);
	ft_wait_for_process(philos, count);
	ft_destoy_semaphores(philos);
	return (0);
}
