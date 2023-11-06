/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/06 13:12:42 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

// rewrite everything and basically have getter functions for if the fork is locked
// and also for alot of data in the philo itself. Might add a mutex to just lock
// the whole philosopher up when retrieving data or adding to it
// actuall not nececary for philo data as it is only accessed by the philo itself
// actually my new termination checker by the main thread is accessing it all over
// but I already added a mutex for the term bool but might also have to add more
// to also be able to check lifecount and eatcount safely

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
	pthread_mutex_t	bool_mutex;
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
	t_lifedata		data;
	int				nbr;
	int				eatcount;
	long			lifecount;
	t_fork			own;
	t_fork			*right;
	pthread_mutex_t	term_mutex;
	char			terminate;
}	t_philo;

//utils.c
int		ft_isdigit(char c);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

//initialize_philosophers.c
int		ft_destroy_philosophers(int err, t_philo *phil, int count);
int		ft_init_philosophers(t_philo *philos, int count, t_lifedata *data);
int		ft_init_data(int argc, char **argv, t_lifedata *data);

//philo.c
long	ft_eat(t_philo *philo);
void	*ft_philo_main(void *void_philo);
int		ft_start_philos(t_philo *philos, int count);
int		ft_wait_philos(t_philo *philos, int count);

//time.c
long	ft_tvtms(struct timeval *tv);
long	ft_currtime(void);
long	ft_gcts(long start);
void	ft_print_mutlti(char *str, long timestamp, int nbr);

//forks.c
int		ft_lock(t_fork	*fork);
int		ft_unlock(t_fork *fork);
int		ft_took_forks(t_philo *philo);
int		ft_drop_forks(t_philo *philo);

#endif //!PHILO_H
