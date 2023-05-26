/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:24:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/26 17:34:15 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

void	ft_init_philo(t_mainst *table, int i)
{
	table->philos[i].table = table;
	table->philos[i].t1 = table->tid[i];
	table->philos[i].id = i;
	table->philos[i].dead = 0;
	table->philos[i].eating = 0;
	table->philos[i].sleeping = 0;
	table->philos[i].time_to_die = table->time_die;
	pthread_mutex_init(&table->philos[i].lock, NULL);
	table->philos[i].r_fork = &table->forks[i];
	table->philos[i].l_fork = &table->forks[(i + 1) % table->nb_philo];
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	philo->last_eat_time = ft_get_time();
	printf("\nPhilosopher %d is eating", philo->id);
	ft_usleep_checkdeath(philo, philo->table->time_eat);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
}

void	ft_sleep(t_philo *philo)
{
	printf("\nPhilosopher %d is sleeping ", philo->id);
	ft_usleep_checkdeath(philo, philo->table->time_sleep);
}

void	*thread_routine(t_philo *philo)
{
	while (//check la mort
	printf("\nPhilosopher %d is thinking ", philo->id);
	pthread_mutex_lock(&forks[n]);//when philosopher 5 is eating he takes fork 1 and fork 5
	ft_eat(philo);
	ft_sleep(philo);
}

int	ft_init_diner(t_mainst *table)
{
	int		i;
	int		k;
	int		j;

	table->philos = malloc(table->nb_philo * sizeof(t_philo));
	table->tid = malloc(table->nb_philo * sizeof(pthread_t));
	table->forks = malloc(table->nb_philo * sizeof(pthread_t));
	if (!table->tid || !table->forks)
		return (0);
	i = -1;
	while (++i < table->nb_philo)
		j = pthread_mutex_init(&table->forks[i], NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		ft_init_philo(table, i);
		k = pthread_create(&table->tid[i], NULL, thread_routine, &table->philos[i]);
	}
	if (k == -1 || j == -1)
		return (0);
}


int	ft_philosopher(int argc, char **argv)
{
	t_mainst	table;
	int			i;

	if (!ft_philo_parsing(argc, argv, &table))
		return (1);
	if (!ft_init_diner(&table))
		return (1);
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