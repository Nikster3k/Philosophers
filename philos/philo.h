/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/08 14:59:38 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

# define MALLOC_FAIL 2
# define BAD_ARGS 3
# define MUTEX_INITFAIL 4

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	bool_mutex;
	int				idx;
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

typedef enum e_state
{
	RUNNING,
	DONE,
	TERMINATE
}	t_state;

typedef struct s_philo
{
	pthread_t		tid;
	t_lifedata		data;
	int				nbr;
	int				eatcount;
	long			lasteat;
	t_fork			own;
	t_fork			*right;
	pthread_mutex_t	term_mutex;
	t_state			state;
}	t_philo;

//utils.c
int		ft_isdigit(char c);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

//initialize_philosophers.c
int		ft_destroy_philosophers(int err, t_philo *phil, int count);
int		ft_init_philosophers(t_philo *philos, int count, t_lifedata *data);
int		ft_init_data(int argc, char **argv, t_lifedata *data);

int		ft_start_philos(t_philo *philos, int count);
//philo.c
long	ft_try_eat(t_philo *philo);
void	*ft_philo_main(void *void_philo);
int		ft_wait_philos(t_philo *philos, int count);
int		ft_get_philo_state(t_philo *philo);
void	ft_set_philo_state(t_philo *philo, int val);
//time.c
long	ft_tvtms(struct timeval *tv);
long	ft_currtime(void);
long	ft_gcts(long start);
void	ft_print_multi(char *str, t_philo *philo);

//forks.c
int		ft_lock(t_fork	*fork);
int		ft_unlock(t_fork *fork);
int		ft_took_forks(t_philo *philo);
int		ft_drop_forks(t_philo *philo);
int		ft_fork_check(t_fork *fork);

#endif //!PHILO_H
