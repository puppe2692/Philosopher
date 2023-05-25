/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:24:29 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/25 17:04:36 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

void	*thread_routine(void *table)
{
	
}

void	ft_thread_creation(t_mainst *table, int i)
{
	pthread_t	tid1;
	t_philo		philo;

	pthread_create(&tid1, NULL, thread_routine, &count);
}


int	ft_philosopher(int argc, char **argv)
{
	t_mainst	table;
	int			i;

	if (!ft_philo_parsing(argc, argv, &table))
		return (1);
	i = -1;
	while (++i < table.nb_philo)
		ft_thread_creation(&table, i);
	return (0);
}
