/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/12 22:35:48 by nsassenb         ###   ########.fr       */
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
	pthread_t		owner;
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
void	ft_print_action(char *str, t_philo *philo);
int		ft_isdigit(char c);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

//initialize_philosophers.c
int		ft_destroy_philosophers(int err, t_philo *phil, int count);
int		ft_init_philosophers(t_philo *philos, int count, t_lifedata *data);
int		ft_init_data(int argc, char **argv, t_lifedata *data);

int		ft_start_philos(t_philo *philos, int count);
//philo.c
int		ft_try_eat(t_philo *philo);
void	*ft_philo_main(void *void_philo);
int		ft_wait_philos(t_philo *philos, int count);
int		ft_get_philo_state(t_philo *philo);
void	ft_set_philo_state(t_philo *philo, int val);

//philo_utils.c
int		ft_philo_check_death(t_philo *philo);
void	ft_philo_sleep(t_philo *philo, int sleep_ms);
void	ft_philo_die(t_philo *philo);
void	*ft_philo_solo(void *philo_void);

//time.c
long	ft_tvtms(struct timeval *tv);
long	ft_currtime(void);
long	ft_gcts(long start);

//forks.c
int		ft_trylock(t_philo *philo, t_fork *fork);
int		ft_tryunlock(t_philo *philo, t_fork *fork);
int		ft_fork_check(t_philo *philo, t_fork *fork);
int		ft_took_forks(t_philo *philo);
int		ft_drop_forks(t_philo *philo);

//fork_utils.c
pthread_t	ft_get_owner(t_fork *fork);
void		ft_set_owner(t_fork *fork, pthread_t tid);

#endif //!PHILO_H
