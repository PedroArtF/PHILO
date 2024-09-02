/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:29:07 by parthur-          #+#    #+#             */
/*   Updated: 2024/08/30 20:29:07 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setting_starting_time(t_dinner_manager *manager)
{
	struct timeval		start;
	int					i;

	i = 0;
	gettimeofday(&start, NULL);
	manager->start = (start.tv_sec * 1000000 + start.tv_usec);
	while (i < manager->data->number_of_philosophers)
	{
		manager->philos[i].start_time = manager->start;
		manager->philos[i].last_meal = manager->start;
		i++;
	}
}

void	thread_creator_func(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->number_of_philosophers)
	{
		pthread_create(&philos[i].philosopher,
			NULL, &dinner_routine, &philos[i]);
		i++;
	}
}

void	thread_join_func(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].data->number_of_philosophers)
	{
		pthread_join(philos[i].philosopher, NULL);
		i++;
	}
}

void	mutex_destroyer_function(t_dinner_manager *manager)
{
	int	i;

	i = 0;
	while (i < manager->data->number_of_philosophers)
	{
		pthread_mutex_destroy(&manager->philos[i].philo_fork);
		pthread_mutex_destroy(&manager->philos[i].dinner_validation);
		i++;
	}
	pthread_mutex_destroy(&manager->simulation_tester);
}

void	start_simulation(t_dinner_manager *manager)
{
	*manager->data->simulation_state = TRUE;
	setting_starting_time(manager);
	thread_creator_func(manager->philos);
	pthread_create(&manager->dinner_supervisor, NULL, &dinner_monitoring, &manager);
	thread_join_func(manager->philos);
	pthread_join(manager->dinner_supervisor, NULL);
	mutex_destroyer_function(manager);
}
