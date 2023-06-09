/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:36:19 by nwyseur           #+#    #+#             */
/*   Updated: 2023/05/29 17:48:53 by nwyseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

// Each thread will count TIMES_TO_COUNT times
#define TIMES_TO_COUNT 21000

#define NC	"\e[0m"
#define YELLOW	"\e[1;33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

// thread_routine is the function the thread invokes right after its
// creation. The thread ends at the end of this function.

void	*thread_routine(void *data)
{
	// Each thread starts here
	pthread_t	tid;
	unsigned int	*count; // pointer to the variable created in main
	unsigned int	i;

	tid = pthread_self();
	count = (unsigned int *)data;
	// Print the count before this thread starts iterating:
	printf("%sThread [%ld]: Count at thread start = %u.%s\n",
		YELLOW, tid, *count, NC);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		// Iterate TIMES_TO_COUNT times
		// Increment the counter at each iteration
		(*count)++;
		i++;
	}
	// Print the final count when this thread
	// finishes its own count
	printf("%sThread [%ld]: Final count = %u.%s\n",
		BYELLOW, tid, *count, NC);
	return (NULL); // Thread ends here.

}


int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	// Variable to keep track of the threads' counts:
	unsigned int	count;

	count = 0;
	// Since each thread counts TIMES_TO_COUNT times and that
	// we have 2 threads, we expect the final count to be
	// 2 * TIMES_TO_COUNT:
	printf("Main: Expected count is %s%u%s\n", GREEN, 
					2 * TIMES_TO_COUNT, NC);
	// Thread creation:
	pthread_create(&tid1, NULL, thread_routine, &count);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &count);
	printf("Main: Created second thread [%ld]\n", tid2);
	// Thread joining:
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid2);
	// Final count evaluation:
	if (count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR ! Total count is %u%s\n", RED, count, NC);
	else
		printf("%sMain: OK. Total count is %u%s\n", GREEN, count, NC);
	return (0);
}


	if (table->dead == 1)
	{
		i = -1;
		while (++i < table->nb_philo)
		{
			if (table->philos[i].dead == 1)
				printf("\n%i Philosopher %d is Dead ",
					ft_get_time() - table->time_start, table->philos[i].id);
		}
	}
	return (1);