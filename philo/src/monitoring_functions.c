/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:23:50 by parthur-          #+#    #+#             */
/*   Updated: 2024/09/05 20:55:30 by parthur-         ###   ########.fr       */
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

void	philosophers_killer(t_dinner_manager *manager, int i)
{
	char	*died_time;

	died_time = NULL;
	died_time = get_action_time_str(&manager->philos[i], died_time);
	pthread_mutex_lock(&manager->dinner_validation);
	if (manager->data->number_of_times_each_philosopher_must_eat == \
				manager->philos[i].number_of_meals)
		printf("EVERYONE IS SATISFIED\n");
	else
		printf("%s PHILO %d DIED\n", died_time, manager->philos[i].id);
	manager->data->simulation_state = FALSE;
	pthread_mutex_unlock(&manager->dinner_validation);
	free(died_time);
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
			time_now = get_simulation_time(MICROSECONDS, \
					manager->philos[i].last_meal);
			if (time_now / 1000 > manager->data->time_to_die)
			{
				philosophers_killer(manager, i);
				break ;
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}
