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
	//pthread_mutex_init(&data->dinner_validation, NULL);
	data->number_of_philosophers = ft_atoli(argv[1]);
	data->time_to_die = ft_atoli(argv[2]);
	data->time_to_eat = ft_atoli(argv[3]) * 1e3;
	data->time_to_sleep = ft_atoli(argv[4]) * 1e3;
	data->number_of_times_each_philosopher_must_eat = -1;
	data->simulation_state = FALSE;
	if (argv[5] != NULL)
		data->number_of_times_each_philosopher_must_eat = ft_atoli(argv[5]);
	return (data);
}

void	initializing_right_forks(t_philo *philos, int number_of_philos)
{
	int	i;

	i = 0;
	while (i < number_of_philos)
	{
		philos[i].right_fork = &philos[(i + 1) % number_of_philos].philo_fork;
		i++;
	}
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
	philo = malloc(sizeof(t_philo) * (data->number_of_philosophers + 1));
	if (!philo)
		return (NULL);
	memset(philo, '\0', (sizeof(t_philo) * (data->number_of_philosophers + 1)));
	while (i <= data->number_of_philosophers)
	{
		philo[i].data = data;
		philo[i].id = id;
		philo[i].last_meal = 0;
		philo[i].number_of_meals = 0;
		philo[i].dinner_validation = &manager->dinner_validation;
		//pthread_mutex_init(&philo[i].dinner_validation, NULL);
		pthread_mutex_init(&philo[i].philo_fork, NULL);
		philo[i].data->simulation_state = &manager->simulation_state;
		i++;
		id++;
	}
	initializing_right_forks(philo, data->number_of_philosophers);
	return (philo);
}

t_dinner_manager	*initializing_manager(char **argv)
{
	t_dinner_manager	*manager;

	manager = (t_dinner_manager *)malloc(sizeof(t_dinner_manager) * 1);
	manager->simulation_state = TRUE;
	pthread_mutex_init(&manager->dinner_validation, NULL);
	manager->philos = initializing_philos(argv, manager);
	//manager->data = manager->philos[0].data;
	//pthread_mutex_init(&manager->simulation_tester, NULL);
	manager->start = 0;
	manager->time_now = 0;
	manager->last_time = 0;
	manager->data = manager->philos[0].data;
	//manager->data = initializing_philo_data(argv);
	return (manager);
}
