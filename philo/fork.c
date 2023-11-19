/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:58:26 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/19 15:05:52 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	ft_get_fork_owner(t_fork *fork)
{
	pthread_t	tid;

	pthread_mutex_lock(&fork->bool_mutex);
	tid = fork->owner;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (tid);
}

int	ft_set_fork_owner(t_fork *fork, pthread_t new)
{
	pthread_mutex_lock(&fork->bool_mutex);
	if (new != 0 && fork->owner != 0)
	{
		pthread_mutex_unlock(&fork->bool_mutex);
		return (0);
	}
	fork->owner = new;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (1);
}
