/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:30:49 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/27 18:38:33 by nwyseur          ###   ########.fr       */
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
}
