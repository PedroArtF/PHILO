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
	int				i;
	enum e_error	error;

	i = 0;
	while (i < philos[0].data->number_of_philosophers)
	{
		error = pthread_create(&philos[i].philosopher,
				NULL, &dinner_routine, &philos[i]);
		if (error != NOERROR)
			error_msg_thread_create(error, philos[i].id);
		i++;
	}
}

void	thread_join_func(t_philo *philos)
{
	int				i;
	enum e_error	error;

	i = 0;
	while (i < philos[0].data->number_of_philosophers)
	{
		error = pthread_join(philos[i].philosopher, NULL);
		if (error != NOERROR)
			error_msg_thread_join(error, philos[i].id);
		i++;
	}
}

void	free_memory_and_destroy_lock(t_dinner_manager *manager)
{
	int				i;
	int				nb_philo;
	enum e_error	error;

	i = 0;
	nb_philo = manager->data->number_of_philosophers;
	while (i < nb_philo)
	{
		error = pthread_mutex_destroy(&manager->philos[i].philo_fork);
		if (error != NOERROR)
			error_msg_mutex_destroy(error);
		i++;
	}
	error = pthread_mutex_destroy(&manager->dinner_validation);
	if (error != NOERROR)
		error_msg_mutex_destroy(error);
	free(manager->data);
	free(manager->philos);
	free(manager);
}

void	start_simulation(t_dinner_manager *manager)
{
	enum e_error	error;

	*manager->data->simulation_state = TRUE;
	setting_starting_time(manager);
	thread_creator_func(manager->philos);
	error = pthread_create(&manager->dinner_supervisor, \
			NULL, &dinner_monitoring, manager);
	if (error != NOERROR)
		error_msg_thread_create(error, \
			(manager->data->number_of_philosophers + 1));
	thread_join_func(manager->philos);
	error = pthread_join(manager->dinner_supervisor, NULL);
	if (error != NOERROR)
		error_msg_thread_join(error, \
			(manager->data->number_of_philosophers + 1));
	free_memory_and_destroy_lock(manager);
}
