/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_includes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:17:28 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/25 19:02:39 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INCLUDES_H
# define PHILO_INCLUDES_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <pthread.h>

typedef struct main_struct
{
	pthread_t			*tid;
	pthread_mutex_t		*forks;
	int					nb_philo;
	int					philo_id;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					nb_meal;
	int					dead;
	int					finished;
	t_philo				*philos;

}	t_mainst;

typedef struct s_philo
{
	struct main_struct	*table;
	pthread_t			t1;
	int					id;
	int					eat_cont;
	int					status;
	int					eating;
	int					time_to_die;
	pthread_mutex_t		lock;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

// Main
int	ft_philosopher(int argc, char **argv);

//Parsing
int	ft_philo_parsing(int argc, char **argv, t_mainst *table);
int	ft_init_args(int argc, char **argv, t_mainst *table);
int	ft_parsnumvalue(char *arg);

#endif