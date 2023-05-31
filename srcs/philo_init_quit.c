/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_quit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:30:49 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/31 15:54:42 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

int	ft_init_mutex(t_mainst *table)
{
	int	i;
	int	j;

	i = -1;
	while (++i < table->nb_philo)
	{
		j = pthread_mutex_init(&table->forks[i], NULL);
		if (j == -1)
			return (0);
	}
	j = pthread_mutex_init(&table->printf, NULL);
	if (j == -1)
		return (0);
	j = pthread_mutex_init(&table->death, NULL);
	if (j == -1)
		return (0);
	j = pthread_mutex_init(&table->fin, NULL);
	if (j == -1)
		return (0);
	j = pthread_mutex_init(&table->repas, NULL);
	if (j == -1)
		return (0);
	return (1);
}

int	ft_init_thread(t_mainst *table)
{
	int	i;
	int	j;

	i = -1;
	while (++i < table->nb_philo)
	{
		ft_init_philo(table, i);
		j = pthread_create(&table->tid[i], NULL,
				thread_routine, &table->philos[i]);
		if (j == -1)
			return (0);
	}
	return (1);
}

void	ft_free_table(t_mainst *table)
{
	if (table->tid)
		free(table->tid);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

void	ft_exit(t_mainst *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->printf);
	pthread_mutex_destroy(&table->death);
	ft_free_table(table);
}
