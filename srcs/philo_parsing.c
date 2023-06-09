/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:36:26 by nwyseur           #+#    #+#             */
/*   Updated: 2023/06/01 12:37:54 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

int	ft_parsnumvalue(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("Arguments must be numeric value");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_init_args(int argc, char **argv, t_mainst *table)
{
	table->nb_philo = ft_atoi(argv[1]);
	if (table->nb_philo < 1 || table->nb_philo > 200)
	{
		printf(
			"Philosophers can't philosoph with this amount of philosophers\n");
		return (0);
	}
	table->time_die = ft_atoi(argv[2]);
	table->time_eat = ft_atoi(argv[3]);
	table->time_sleep = ft_atoi(argv[4]);
	if (table->time_die < 1 || table->time_eat < 1 || table->time_sleep < 1)
	{
		printf("Time is not an imaginary concept\n");
		return (0);
	}
	if (argc == 6)
		table->nb_meal = ft_atoi(argv[5]);
	else
		table->nb_meal = 0;
	if (argc == 6 && table->nb_meal < 1)
	{
		printf("Who wants to eat around a table with no food?\n");
		return (0);
	}
	return (1);
}

int	ft_philo_parsing(int argc, char **argv, t_mainst *table)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_parsnumvalue(argv[i]))
			return (0);
		i++;
	}
	if (!ft_init_args(argc, argv, table))
		return (0);
	return (1);
}
