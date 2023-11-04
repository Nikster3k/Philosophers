/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/04 19:00:00 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

enum e_errors
{
	SUCCESS = 0,
	BAD_ARGS,
	MALLOC_FAIL,
	MUTEX_INITFAIL,
};

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	char			is_locked;
}	t_fork;

typedef struct s_lifedata
{
	long	st;
	int		ttd;
	int		tte;
	int		tts;
	int		mineat;
}	t_lifedata;

typedef struct s_philo
{
	pthread_t		tid;
	t_lifedata		*data;
	int				nbr;
	int				eatcount;
	long			lifecount;
	t_fork			own;
	t_fork			*right;
}	t_philo;

//utils.c
int		ft_isdigit(char c);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

//initialize_philosophers.c
int		ft_destroy_philosophers(int err, t_philo *phil, int count);
int		ft_init_philosophers(t_philo *philos, int count, t_lifedata *data);
int		ft_init_data(int argc, char **argv, t_lifedata *data);

//time.c
long	ft_tvtms(struct timeval *tv);
long	ft_currtime(void);
long	ft_gcts(long start);

//forks.c
int		ft_lock(t_fork	*fork);
int		ft_unlock(t_fork *fork);
int		ft_took_forks(t_philo *philo);
int		ft_drop_forks(t_philo *philo);

#endif //!PHILO_H