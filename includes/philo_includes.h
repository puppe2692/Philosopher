/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_includes.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:17:28 by nwyseur           #+#    #+#             */
/*   Updated: 2023/06/13 14:53:47 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_INCLUDES_H
# define PHILO_INCLUDES_H

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct main_struct	*table;
	pthread_t			t1;
	int					id;
	int					dead;
	unsigned long		eat_count;
	int					fat;
	unsigned long		last_eat_time;
	unsigned long		time_to_die;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct main_struct
{
	pthread_t			*tid;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printf;
	pthread_mutex_t		death;
	pthread_mutex_t		fin;
	pthread_mutex_t		repas;
	int					nb_philo;
	unsigned long		time_die;
	unsigned long		time_eat;
	unsigned long		time_sleep;
	unsigned long		time_start;
	unsigned long		nb_meal;
	int					dead;
	int					finished;
	int					full;
	t_philo				*philos;

}	t_mainst;

// Main
int				ft_philosopher(int argc, char **argv);
int				ft_init_diner(t_mainst *table);
void			ft_init_philo(t_mainst *table, int i);
int				ft_init_mutex(t_mainst *table);
int				ft_init_thread(t_mainst *table);

//Parsing	
int				ft_philo_parsing(int argc, char **argv, t_mainst *table);
int				ft_init_args(int argc, char **argv, t_mainst *table);
int				ft_parsnumvalue(char *arg);

//action	
int				ft_isdead(t_philo	*philo);
int				ft_forks(t_philo *philo,
					pthread_mutex_t *r_fork, pthread_mutex_t *l_fork);
int				ft_take_forks(t_philo *philo);
int				ft_eat(t_philo *philo);
int				ft_sleep(t_philo *philo);
int				ft_think(t_philo *philo);
void			*thread_routine(void *philos);

//utils & quit
unsigned long	ft_get_time(void);
void			ft_print_death(t_philo *philo);
int				ft_usleep_check_death(t_philo *philo, unsigned long time);
int				ft_watch_death(t_philo *philo);
void			ft_free_table(t_mainst *table);
void			ft_exit(t_mainst *table);

//lib	
unsigned long	ft_atoi(const char *str);
int				ft_isdigit(int c);

#endif