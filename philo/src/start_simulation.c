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

void	setting_starting_time(t_dinner_manager *manager)
{
	 struct timeval		start;
	 int				i;

	i = 0;
    gettimeofday(&start, NULL);
	manager->start = (start.tv_sec * 1000 + start.tv_usec / 1000);
	while (i < manager->data->number_of_philosophers) 
	{
		manager->philos[i].start_time = manager->start;
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

void	start_simulation(t_dinner_manager *manager)
{
	int	number_of_meals;

	number_of_meals = 0;
	manager->data->simulation_state = TRUE;
	setting_starting_time(manager);
	while (checking_simulation_status(manager))
	{
		thread_creator_func(manager->philos);
		thread_join_func(manager->philos);
		if (++number_of_meals == manager->data->number_of_times_each_philosopher_must_eat)
			manager->data->simulation_state = FALSE;
	}
}
