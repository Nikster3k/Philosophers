/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/23 14:27:42 by nsassenb         ###   ########.fr       */
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
# define FAIL_THREAD 5

typedef enum e_state
{
	RUNNING,
	DONE,
	TERMINATE,
	STOP
}	t_state;

typedef struct s_lifedata
{
	long	st;
	int		ttd;
	int		tte;
	int		tts;
	int		mineat;
}	t_lifedata;

typedef struct s_simdata
{
	pthread_mutex_t	sim_mutex;
	t_state			state;
}	t_sim;

typedef struct s_philo
{
	pthread_t		tid;
	t_lifedata		data;
	int				nbr;
	int				eatcount;
	long			lasteat;
	pthread_mutex_t	own;
	pthread_mutex_t	*right;
	t_state			state;
	pthread_mutex_t	data_mutex;
	t_sim			*sim;
}	t_philo;

//main.c
void		ft_wait_threads(t_philo *philos, int count);

//philo_sim.c
void		ft_sim_set_state(t_philo *philo, t_state new_state);
int			ft_sim_get_state(t_philo *philo);
int			ft_wait_philos(t_philo *philos, int count);
void		ft_philos_set_state(t_philo *philos, int count, t_state state);
void		*ft_philo_solo(void *data);

//philo_utils.c
int			ft_get_philo_state(t_philo *philo);
void		ft_set_philo_state(t_philo *philo, int val);
int			ft_lock_forks(t_philo *philo);
void		ft_unlock_forks(t_philo *philo);

//philo.c
void		ft_kill_philo(t_philo *philo);
int			ft_check_death(t_philo *philo);
void		ft_philo_sleep(t_philo *philo, int time_ms);
int			ft_philo_action(t_philo *philo);
void		*ft_philo_main(void *data);

//utils.c
int			ft_isdigit(char c);
long		ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);

//print_mutli.c
void		ft_print_action(char *str, t_philo *philo);

//initialize_philosophers.c
int			ft_destroy_philosophers(int err, t_philo *phil, int count);
int			ft_init_philosophers(t_philo *philos, int count,
				t_lifedata *data, t_sim *sim);
int			ft_init_data(int argc, char **argv, t_lifedata *data);

//time.c
long		ft_tvtms(struct timeval *tv);
long		ft_currtime(void);
long		ft_gcts(t_philo *philo);

#endif //!PHILO_H
