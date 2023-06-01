/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:43:21 by nwyseur           #+#    #+#             */
/*   Updated: 2023/06/01 12:19:51 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

int	ft_forks(t_philo *philo, pthread_mutex_t *r_fork, pthread_mutex_t *l_fork)
{
	pthread_mutex_lock(r_fork);
	if (ft_watch_death(philo) == 1)
		return (pthread_mutex_unlock(r_fork), 0);
	pthread_mutex_lock(&philo->table->printf);
	printf("\n%i %d has taken a fork",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	pthread_mutex_lock(l_fork);
	if (ft_watch_death(philo) == 1)
		return (pthread_mutex_unlock(r_fork),
			pthread_mutex_unlock(l_fork), 0);
	pthread_mutex_lock(&philo->table->printf);
	printf("\n%i %d has taken a fork",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	return (1);
}

int	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!ft_forks(philo, philo->r_fork, philo->l_fork))
			return (0);
	}
	else
	{
		if (!ft_forks(philo, philo->l_fork, philo->r_fork))
			return (0);
	}
	return (1);
}

int	ft_eat(t_philo *philo)
{
	if (ft_watch_death(philo) == 1)
		return (0);
	if (!ft_take_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->table->printf);
	philo->eat_count++;
	philo->last_eat_time = ft_get_time();
	printf("\n%i %d is eating",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	ft_usleep_check_death(philo, philo->table->time_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_watch_death(philo) == 1)
		return (0);
	pthread_mutex_lock(&philo->table->printf);
	printf("\n%i %d is sleeping",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	ft_usleep_check_death(philo, philo->table->time_sleep);
	return (1);
}

int	ft_think(t_philo *philo)
{
	int	time;
	int	cycle;
	int	nb_philo;
	int	die;

	nb_philo = philo->table->nb_philo;
	die = philo->table->time_die;
	cycle = philo->table->time_eat + philo->table->time_sleep;
	if ((nb_philo % 2 == 0 && die >= cycle
			&& die >= (2 * philo->table->time_eat))
		|| (nb_philo % 2 == 1 && die >= cycle
			&& die >= (3 * philo->table->time_eat)))
		time = 5 * (nb_philo % 2);
	else
		time = philo->table->time_eat * (2 + nb_philo % 2) - cycle;
	if (ft_watch_death(philo) == 1)
		return (0);
	pthread_mutex_lock(&philo->table->printf);
	printf("\n%i %d is thinking",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	ft_usleep_check_death(philo, time);
	if (ft_watch_death(philo) == 1)
		return (0);
	return (1);
}
