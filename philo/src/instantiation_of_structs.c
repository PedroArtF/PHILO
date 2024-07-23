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

t_philo_data    initializing_philo_data(char **argv)
{
    t_philo_data    *data;

    data = malloc(sizeof(t_philo_data) * 2);
    memset(data, '\0', (sizeof(data) * 2));
    data->number_of_philosophers = argv[1];
    data->time_to_die = argv[2];
    data->time_to_eat = argv[3] * 1e3;
    data->time_to_sleep = arvg[4] * 1e3;
    data->number_of_times_each_philosopher_must_eat = -1;
    if (argv[5] != NULL)
        data->number_of_times_each_philosopher_must_eat = argv[5];
    return (data);
}

t_philo    initializing_philo(t_philo_data *data)
{
    t_philo *philo;
    int     i;

    i = 0;
    philo = malloc(sizeof(t_philo) * (data->number_of_philosophers + 1));
    memset(philo, '\0', (sizeof(philo) * (data->number_of_philosophers + 1)));
    while (i < data->number_of_philosophers)
    {
        philo->data = data;
        i++;
    }
}