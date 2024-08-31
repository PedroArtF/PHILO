/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:23:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/08/30 21:10:31 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checking_simulation_status(t_dinner_manager *manager)
{
	int	status;

	status = TRUE;
	pthread_mutex_lock(&manager->simulation_tester);
	if (!manager->data->simulation_state)
		status = FALSE;
	pthread_mutex_unlock(&manager->simulation_tester);
	return (status);
}

void	*dinner_monitoring(void *arg)
{
	long int			time_now;
	t_dinner_manager	*manager;
	int					i;

	i = 0;
	manager = (t_dinner_manager *) arg;
	while (checking_simulation_status(manager))
	{
		while (i < manager->data->number_of_philosophers)
		{
			time_now = get_simulation_time(MICROSECONDS, manager->philos[i].last_meal);
			if (time_now > manager->data->time_to_die)
			{
				pthread_mutex_lock(&manager->simulation_tester);
				printf("o tempo foi = %ld\n", get_simulation_time(MICROSECONDS, manager->philos[i].last_meal));
				manager->simulation_state = FALSE;
				pthread_mutex_unlock(&manager->simulation_tester);
				break;
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}