/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/19 23:57:36 by nsassenb         ###   ########.fr       */
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
	TERMINATE,
	STOP
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
	t_state			state;
	pthread_mutex_t	term_mutex;
	t_state			*term_state;
}	t_philo;

//main.c ??
int			ft_sim_running(t_philo *philo);

//philo_utils.c
int			ft_lock_forks(t_philo *philo);
void		ft_unlock_forks(t_philo *philo);
void		*ft_philo_solo(void *data);
int			ft_fork_unlock(t_philo *philo, t_fork *fork);

//philo.c
void		ft_kill_philo(t_philo *philo);
int			ft_check_death(t_philo *philo);
void		ft_philo_sleep(t_philo *philo, int time_ms);
int			ft_philo_action(t_philo *philo);
void		*ft_philo_main(void *data);

//fork.c
pthread_t	ft_get_fork_owner(t_fork *fork);
int			ft_set_fork_owner(t_fork *fork, pthread_t new);

//utils.c
int			ft_isdigit(char c);
long		ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);

//print_mutli.c
void		ft_print_action(char *str, t_philo *philo, long time_stamp);
void		*ft_print_job(void *void_data);
void		ft_print_action_multi(char *str, t_philo *philo, long time_stamp);

//initialize_philosophers.c
int			ft_destroy_philosophers(int err, t_philo *phil, int count);
int			ft_init_philosophers(t_philo *philos, int count, t_lifedata *data,
				t_state *sim_state);
int			ft_init_data(int argc, char **argv, t_lifedata *data);

//time.c
long		ft_tvtms(struct timeval *tv);
long		ft_currtime(void);
long		ft_gcts(long start);

#endif //!PHILO_H
