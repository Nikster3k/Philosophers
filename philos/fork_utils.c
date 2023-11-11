/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:28:04 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/11 23:36:52 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// get thread id of the owner of the fork
pthread_t	ft_get_owner(t_fork *fork)
{
	pthread_t	ret;

	pthread_mutex_lock(&fork->bool_mutex);
	ret = fork->owner;
	pthread_mutex_unlock(&fork->bool_mutex);
	return (ret);
}

// set thread id when taking the fork
void	ft_set_owner(t_fork *fork, pthread_t tid)
{
	pthread_mutex_lock(&fork->bool_mutex);
	fork->owner = tid;
	pthread_mutex_unlock(&fork->bool_mutex);
}
