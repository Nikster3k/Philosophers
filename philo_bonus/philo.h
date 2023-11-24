/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/24 15:33:10 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define MALLOC_FAIL 2
# define BAD_ARGS 3
# define SEM_FAIL 4
# define FAIL_THREAD 5

# define SEMAPHORE_FORKS "/forks_sema"
# define SEMAPHORE_PRINT "/print_sema"
# define SEMAPHORE_KILLER "/killer_sema"

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

typedef struct s_philo
{
	pthread_t		tid;
	t_lifedata		data;
	int				nbr;
	int				eatcount;
	long			lasteat;
	t_state			state;
	sem_t			*forks;
	sem_t			*print_sema;
	sem_t			*sim;
	sem_t			*self;
}	t_philo;

//philo_utils.c
void		ft_philo_eat(t_philo *philo);
int			ft_get_philo_state(t_philo *philo);
void		ft_set_philo_state(t_philo *philo, int val);
int			ft_lock_forks(t_philo *philo);
void		ft_unlock_forks(t_philo *pholo);

//philo.c
void		ft_kill_philo(t_philo *philo);
int			ft_check_death(t_philo *philo);
int			ft_philo_action(t_philo *philo);
void		ft_philo_main(t_philo *self);

//utils.c
int			ft_isdigit(char c);
long		ft_atol(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);

//print_mutli.c
void		ft_print_action(char *str, t_philo *philo);

//initialize_philosophers.c
int			ft_init_data(int argc, char **argv, t_lifedata *data);

//time.c
void		ft_philo_sleep(t_philo *philo, int time_ms);
long		ft_tvtms(struct timeval *tv);
long		ft_currtime(void);
long		ft_gcts(t_philo *philo);

#endif //!PHILO_H
