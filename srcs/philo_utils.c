/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:29:04 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/31 15:20:18 by nwyseur          ###   ########.fr       */
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


void	ft_print_death(t_philo *philo)
{
	int	check;

	pthread_mutex_lock(&philo->table->fin);
	check = philo->table->finished;
	pthread_mutex_unlock(&philo->table->fin);
	if (check == 0)
	{
		pthread_mutex_lock(&philo->table->fin);
		philo->table->finished = 1;
		pthread_mutex_unlock(&philo->table->fin);
		pthread_mutex_lock(&philo->table->death);
		philo->table->dead = philo->id;
		pthread_mutex_lock(&philo->table->printf);
		printf("\n%i %d died",
			ft_get_time() - philo->table->time_start, philo->id);
		pthread_mutex_unlock(&philo->table->printf);
		pthread_mutex_unlock(&philo->table->death);
	}

}

int	ft_usleep_check_death(t_philo *philo, int time)
{
	int	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
	{
		usleep(1000);
		if (ft_get_time() - philo->last_eat_time > philo->time_to_die)
			ft_print_death(philo);
		if (philo->eat_count >= philo->table->nb_meal
			&& philo->table->nb_meal > 0 && philo->fat == 0)
		{
			philo->fat = 1;
			pthread_mutex_lock(&philo->table->repas);
			philo->table->full++;
			pthread_mutex_unlock(&philo->table->repas);
		}
	}
	return (0);
}

int	ft_watch_death(t_philo *philo)
{
	int	check;
	int	check2;

	pthread_mutex_lock(&philo->table->death);
	check = philo->table->dead;
	pthread_mutex_unlock(&philo->table->death);
	pthread_mutex_lock(&philo->table->repas);
	check2 = philo->table->full;
	pthread_mutex_unlock(&philo->table->repas);
	if (check != 0)
		return (1);
	if (check2 == philo->table->nb_philo)
		return (1);
	return (0);
}
