/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instantiation_of_structs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:42:32 by marvin            #+#    #+#             */
/*   Updated: 2024/07/22 11:42:32 by marvin           ###   ########.fr       */
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
	if (argv[5] != NULL)
		data->number_of_times_each_philosopher_must_eat = ft_atoli(argv[5]);
	return (data);
}

t_philo	*initializing_philo(char **argv)
{
	t_philo			*philo;
	t_philo_data	*data;
	int				id;
    int             i;

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
        i++;
		id++;
	}
	return (philo);
}

