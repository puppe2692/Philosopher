/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:24:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/26 12:23:11 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

void	ft_init_philo(t_mainst *table, int i)
{
	table->philos[i].table = table;
	table->philos[i].id = i;
	table->philos[i].dead = 0;
	table->philos[i].eating = 0;
	table->philos[i].sleeping = 0;
	table->philos[i].time_to_die = table->time_die;
	table->philos[i].r_fork = &table->forks[i];
	table->philos[i].l_fork = &table->forks[(i + 1) % table->nb_philo];
}


void	*thread_routine(t_mainst *table)
{
	// fcontion init philo ou la faire avant la creation des mutexs et l'init dedans
	printf("\nPhilosopher %d is thinking ", n);
	pthread_mutex_lock(&forks[n]);//when philosopher 5 is eating he takes fork 1 and fork 5
	pthread_mutex_lock(&forks[(n+1)%5]);
	printf("\nPhilosopher %d is eating ",n);
	sleep(3);
	pthread_mutex_unlock(&forks[n]);
	pthread_mutex_unlock(&forks[(n+1)%5]);
	printf("\nPhilosopher %d is sleeping ",n);
	sleep(3);

	// faire une fonction eat prend oruchette
	// faire une fonction eat plus pose oruchette
	// faire une fonction sleep
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
		k = pthread_create(&table->tid[i], NULL, thread_routine, table);
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