/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/01 14:43:47 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>

typedef struct s_lifedata
{
	int	nbr;
	int	ttd;
	int	tte;
	int	tts;
	int	mineat;
}	t_lifedata;


typedef struct s_philo
{
	pthread_t		tid;
	t_lifedata		data;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_philo;

//utils.c
int		ft_isdigit(char c);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif //!PHILO_H