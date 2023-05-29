/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:29:04 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/29 19:04:33 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

int	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (printf("gettimeofday() ECHEC\n", NULL));
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / (int)1000));
}

int	ft_usleep_check_death(t_philo *philo, int time)
{
	int	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
	{
		usleep(1000);
		if (ft_get_time() - philo->last_eat_time > philo->time_to_die)
		{
			philo->dead = 1;
			pthread_mutex_lock(&philo->table->death);
			philo->table->dead = philo->id;
			pthread_mutex_unlock(&philo->table->death);
		}
	}
	return (0);
}

int	ft_watch_death(t_philo *philo)
{
	if (philo->table->dead != 0)
	{
		printf("\n%i Philosopher %d is Dead ",
			ft_get_time() - philo->table->time_start, philo->table->dead);
		return (1);
	}
	return (0);
}
