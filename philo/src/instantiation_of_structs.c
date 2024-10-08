/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instantiation_of_structs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:24:43 by parthur-          #+#    #+#             */
/*   Updated: 2024/08/30 20:24:43 by parthur-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_data	*initializing_philo_data(char **argv)
{
	t_philo_data	*data;

	data = (t_philo_data *)malloc(sizeof(t_philo_data) * 1);
	if (!data)
		return (NULL);
	data->number_of_philosophers = ft_atoli(argv[1]);
	data->time_to_die = ft_atoli(argv[2]);
	data->time_to_eat = ft_atoli(argv[3]) * 1e3;
	data->time_to_sleep = ft_atoli(argv[4]) * 1e3;
	data->number_of_times_each_philosopher_must_eat = -1;
	data->simulation_state = FALSE;
	if (argv[5] != NULL)
		data->number_of_times_each_philosopher_must_eat = ft_atoli(argv[5]);
	if (data->number_of_philosophers > 200)
		data->number_of_philosophers = 200;
	return (data);
}

void	initializing_right_forks(t_philo *philos, int number_of_philos)
{
	int	i;

	i = 0;
	while (i < number_of_philos && number_of_philos > 1)
	{
		philos[i].right_fork = &philos[(i + 1) % number_of_philos].philo_fork;
		i++;
	}
}

void	assigns_value_to_the_philosopher(t_philo *philo, t_dinner_manager \
			*manager, t_philo_data *data, int id)
{
	enum e_error	error;

	philo->data = data;
	philo->id = id;
	philo->last_meal = 0;
	philo->number_of_meals = 0;
	philo->dinner_validation = &manager->dinner_validation;
	error = pthread_mutex_init(&philo->philo_fork, NULL);
	if (error != NOERROR)
		error_msg_mutex(error, philo->id);
	philo->data->simulation_state = &manager->simulation_state;
}

t_philo	*initializing_philos(char **argv, t_dinner_manager *manager)
{
	t_philo			*philo;
	t_philo_data	*data;
	int				id;
	int				i;

	id = 1;
	i = 0;
	data = initializing_philo_data(argv);
	if (!data)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * \
			(data->number_of_philosophers + 1));
	if (!philo)
		return (NULL);
	memset(philo, '\0', (sizeof(t_philo) * (data->number_of_philosophers + 1)));
	while (i <= data->number_of_philosophers)
	{
		assigns_value_to_the_philosopher(&philo[i], manager, data, id);
		i++;
		id++;
	}
	initializing_right_forks(philo, data->number_of_philosophers);
	return (philo);
}

t_dinner_manager	*initializing_manager(char **argv)
{
	t_dinner_manager	*manager;
	enum e_error		error;

	manager = (t_dinner_manager *)malloc(sizeof(t_dinner_manager) * 1);
	manager->simulation_state = TRUE;
	error = pthread_mutex_init(&manager->dinner_validation, NULL);
	if (error != NOERROR)
		error_msg_mutex(error, 201);
	manager->philos = initializing_philos(argv, manager);
	manager->start = 0;
	manager->time_now = 0;
	manager->last_time = 0;
	manager->data = manager->philos[0].data;
	return (manager);
}
