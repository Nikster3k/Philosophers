/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:54:13 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/20 16:25:49 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(char *str, t_philo *philo, long time_stamp)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	long					start;
	long					end;

	start = ft_currtime();
	if (philo->state != RUNNING || ft_sim_running(philo) != RUNNING)
		return ;
	pthread_mutex_lock(&mutex);
	if (philo->state == RUNNING && ft_sim_running(philo) == RUNNING)
		printf("%ld %i %s\n", time_stamp, philo->nbr, str);
	pthread_mutex_unlock(&mutex);
	end = ft_currtime();
	printf("%i spent time in print %ld\n", philo->nbr, end - start);
}
