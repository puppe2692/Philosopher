/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:13:26 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/24 18:22:10 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_includes.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_printf_fd(2, "Wrong number of arguments");
		return (1);
	}
	return (ft_philosopher(argc, argv));
}