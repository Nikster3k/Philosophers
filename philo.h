/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/02 15:35:41 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum e_errors
{
	SUCCESS = 0,
	MALLOC_FAIL,
	MUTEX_INITFAIL,
};

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
	float			lifecount;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}	t_philo;

//utils.c
int		ft_isdigit(char c);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

//initialize_philosophers.c
int		ft_destroy_philosophers(int err, t_philo *phil, int count);
int		ft_init_philosophers(t_philo *philos, int count, t_lifedata data);
int		ft_init_data(int argc, char **argv, t_lifedata *data);

#endif //!PHILO_H