/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:24:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/29 19:09:21 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

void	ft_init_philo(t_mainst *table, int i)
{
	table->philos[i].table = table;
	table->philos[i].t1 = table->tid[i];
	table->philos[i].id = i + 1;
	table->philos[i].dead = 0;
	table->philos[i].eat_count = 0;
	table->philos[i].eating = 0;
	table->philos[i].sleeping = 0;
	table->philos[i].time_to_die = table->time_die;
	table->philos[i].r_fork = &table->forks[i];
	table->philos[i].l_fork = &table->forks[(i + 1) % table->nb_philo];
}

int	ft_eat(t_philo *philo)
{
	if (ft_watch_death(philo) == 1)
		return (0);
	pthread_mutex_lock(philo->r_fork);
	if (ft_watch_death(philo) == 1)
		return (pthread_mutex_unlock(philo->r_fork), 0);
	pthread_mutex_lock(&philo->table->printf);
	printf("\n%i Philosopher %d is taking a fork",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	pthread_mutex_lock(philo->l_fork);
	if (ft_watch_death(philo) == 1)
		return (pthread_mutex_unlock(philo->l_fork), 0);
	pthread_mutex_lock(&philo->table->printf);
	printf("\n%i Philosopher %d is taking a fork",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	pthread_mutex_lock(&philo->table->printf);
	philo->last_eat_time = ft_get_time();
	printf("\n%i Philosopher %d is eating",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	philo->eating = 1;
	philo->eat_count += 1;
	ft_usleep_check_death(philo, philo->table->time_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->printf);
	if (ft_watch_death(philo) == 1)
		return (pthread_mutex_unlock(&philo->table->printf), 0);
	printf("\n%i Philosopher %d is sleeping ",
		ft_get_time() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->printf);
	philo->sleeping = 1;
	ft_usleep_check_death(philo, philo->table->time_sleep);
	philo->sleeping = 0;
	return (1);
}

void	*thread_routine(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos; // pourquoi?
	while (philo->table->dead == 0)
	{
		if (ft_watch_death(philo) == 1)
			return (NULL);
		pthread_mutex_lock(&philo->table->printf);
		printf("\n%i Philosopher %d is thinking ",
			ft_get_time() - philo->table->time_start, philo->id);
		pthread_mutex_unlock(&philo->table->printf);
		if (!ft_eat(philo))
			return (NULL);
		if (!ft_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

int	ft_init_diner(t_mainst *table)
{
	int		i;

	table->philos = malloc(table->nb_philo * sizeof(t_philo));
	table->tid = malloc(table->nb_philo * sizeof(pthread_t));
	table->forks = malloc(table->nb_philo * sizeof(pthread_mutex_t));
	if (!table->tid || !table->forks)
		return (0);
	if (!ft_init_mutex(table))
		return (0);
	if (!ft_init_thread(table))
		return (0);
	i = -1;
	while (++i < table->nb_philo)
		pthread_join(table->tid[i], NULL);
	ft_exit(table);
	return (1);
}


int	ft_philosopher(int argc, char **argv)
{
	t_mainst	table;

	if (!ft_philo_parsing(argc, argv, &table))
		return (1);
	table.time_start = ft_get_time();
	if (!ft_init_diner(&table))
		return (1);
	return (0);
}





/*	
	i = -1;
	while (++i < table.nb_philo)
		ft_thread_creation(&table, i);
	return (0);

void	ft_thread_creation(t_mainst *table, int i)
{
	pthread_t	tid1;
	t_philo		philo;

	pthread_create(&tid1, NULL, thread_routine, table);
}
*/