/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:54:13 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/21 17:15:54 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(char *str, t_philo *philo)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (ft_get_philo_state(philo) != RUNNING)
		return ;
	pthread_mutex_lock(&mutex);
	if (ft_sim_get_state(philo) == RUNNING)
		printf("%ld %i %s\n", ft_currtime() - philo->data.st, philo->nbr, str);
	pthread_mutex_unlock(&mutex);
}
