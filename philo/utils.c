/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsassenb <nsassenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:45:26 by nsassenb          #+#    #+#             */
/*   Updated: 2023/11/12 22:35:48 by nsassenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(char *str, t_philo *philo)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (ft_get_philo_state(philo) != RUNNING)
		return ;
	pthread_mutex_lock(&mutex);
	if (ft_get_philo_state(philo) != TERMINATE)
		printf("% -8ld % -5i %s\n", ft_gcts(philo->data.st), philo->nbr, str);
	pthread_mutex_unlock(&mutex);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	numb;
	short	sign;

	numb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		nptr++;
		sign = -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && ft_isdigit(*nptr))
	{
		numb *= 10;
		numb += *nptr++ - 48;
	}
	return (numb * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pointer;
	size_t	totalsize;

	totalsize = nmemb * size;
	if (nmemb != 0 && size != 0 && (totalsize / nmemb) != size)
		return (NULL);
	pointer = malloc(totalsize);
	if (pointer == NULL)
		return (NULL);
	while (totalsize--)
		((char *)pointer)[totalsize] = 0;
	return (pointer);
}
