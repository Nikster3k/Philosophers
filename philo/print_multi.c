/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:54:13 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/20 18:31:05 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(char *str, t_philo *philo, long time_stamp)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (philo->state != RUNNING || ft_sim_running(philo) != RUNNING)
		return ;
	pthread_mutex_lock(&mutex);
	printf("%ld %i %s\n", time_stamp, philo->nbr, str);
	pthread_mutex_unlock(&mutex);
}
