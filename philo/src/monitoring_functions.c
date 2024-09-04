/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:23:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/09/04 00:19:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checking_simulation_status(t_dinner_manager *manager)
{
	int	status;

	status = TRUE;
	pthread_mutex_lock(&manager->dinner_validation);
	if (!manager->data->simulation_state)
		status = FALSE;
	pthread_mutex_unlock(&manager->dinner_validation);
	return (status);
}

void	*dinner_monitoring(void *arg)
{
	long int			time_now;
	t_dinner_manager	*manager;
	int					i;

	i = 0;
	manager = (t_dinner_manager *) arg;
	//pthread_mutex_init(&manager->simulation_tester, NULL);
	//printf("teste = %ld\n", manager->philos[0].last_meal);
	while (checking_simulation_status(manager))
	{
		while (i < manager->data->number_of_philosophers)
		{ 
			time_now = get_simulation_time(MICROSECONDS, manager->philos[i].last_meal);
			//printf("o tempo agora é %ld\n", time_now);
			if (time_now / 1000 > manager->data->time_to_die)
			{
				pthread_mutex_lock(&manager->dinner_validation);
				if (manager->data->number_of_times_each_philosopher_must_eat == manager->philos[i].number_of_meals)
					printf("EVERYONE IS SATISFIED\n");
				else
					printf("PHILO %d DIED IN %ld MICROSECONDS\n", manager->philos[i].id, time_now);
				manager->data->simulation_state = FALSE;
				pthread_mutex_unlock(&manager->dinner_validation);
				break;
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}