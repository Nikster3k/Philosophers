/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_multi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:54:13 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/24 15:25:57 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(char *str, t_philo *philo)
{
	if (philo->state != RUNNING)
		return ;
	sem_wait(philo->print_sema);
	if (ft_get_philo_state(philo) == RUNNING)
		printf("%ld %i %s\n", ft_currtime() - philo->data.st, philo->nbr, str);
	sem_post(philo->print_sema);
}
