/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:40:01 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/17 17:59:41 by nsassenb         ###   ########.fr       */
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

# define SEMAPHORE_NAME "/forks_sema"

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
	t_state		state;
}	t_philo;

//philo.c
int		ft_take_forks(t_philo *philo);
int		ft_try_eat(t_philo *philo);
int		ft_philo_main(t_philo *philo);
void	ft_wait_philos(pid_t first, int count);

//philo_utils.c
int		ft_philo_check_death(t_philo *philo);
void	ft_philo_sleep(t_philo *philo, int sleep_ms);
void	ft_philo_die(t_philo *philo);
void	ft_kill_philos(pid_t first, int count);

//initialize_philosophers.c
int		ft_init_data(int argc, char **argv, t_lifedata *data);

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
