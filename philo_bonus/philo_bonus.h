/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/12 23:59:21 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# define SEMAPHORE_FAIL 4
# define FORK_FAIL 5

# define SEMA_NAME_FORKS "/forks_sema"
# define SEMA_NAME_STATUS "/status_sema"

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
	t_lifedata	data;
	int			nbr;
	int			eatcount;
	long		lasteat;
	sem_t		*forks;
	sem_t		*status;
	t_state		state;
}	t_philo;

typedef struct s_observer
{
	pthread_t	tid;
	pid_t		pid;
}	t_observer;

typedef struct s_threaddata
{
	t_observer	*obs;
	int			idx;
	int			count;
}	t_threaddata;

//philo.c
int		ft_try_eat(t_philo *philo);
int		ft_philo_main(t_philo *philo);
int		ft_wait_philos(t_philo *philos, int count);
int		ft_get_philo_state(t_philo *philo);
void	ft_set_philo_state(t_philo *philo, int val);

//philo_utils.c
void	ft_set_state(t_philo *philo, t_state new_state);
int		ft_get_state(t_philo *philo);
int		ft_philo_check_death(t_philo *philo);
void	ft_philo_sleep(t_philo *philo, int sleep_ms);
void	ft_philo_die(t_philo *philo);

//initalize_philosophers.c
int		ft_init_philos(t_philo *philos, int count, t_lifedata data);
int		ft_init_data(int argc, char **argv, t_lifedata *data);

//ft_itoa.c
char	*ft_itoa(int n);
int		ft_strlen(const char *str);

//time.c
long	ft_tvtms(struct timeval *tv);
long	ft_currtime(void);
long	ft_gcts(long start);

//utils.c
void	ft_print_action(char *str, t_philo *philo);
int		ft_isdigit(char c);
long	ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

#endif //!PHILO_BONUS_H
