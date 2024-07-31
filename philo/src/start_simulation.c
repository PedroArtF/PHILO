/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:59:03 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 10:59:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_philo *philo)
{
	int				index_p;
	int				index_j;
	long int		micro_sec;
	long int		sec;
	struct timeval	start;
	struct timeval	end;

	index_j = 0;
	index_p = 0;
	gettimeofday(&start, NULL);
	while (index_p < philo->data->number_of_philosophers)
	{
		pthread_create(&philo[index_p].philosopher,
			NULL, &dinner_routine, &philo[index_p]);
		index_p++;
	}
	usleep(2000000);
	while (index_j < philo->data->number_of_philosophers)
	{
		pthread_join(philo[index_j].philosopher, NULL);
		printf("philo %d encerrou\n", philo[index_j].id);
		index_j++;
	}
	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	micro_sec = end.tv_usec - start.tv_usec;
	if (micro_sec < 0)
	{
		sec--;
		micro_sec += 1000000;
	}
	printf("passaram %ld segundos e %ld micro-segundos\n", sec, micro_sec);
}
