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

void    *dinner_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *) arg;
    printf("o id do philo é %d\n", philo->id);
    return (NULL);
}

void    start_simulation(t_philo *philo)
{
    int index_p;
    int index_j;

    index_j = 0;
    index_p = 0;
    while (index_p < philo->data->number_of_philosophers)
    {
        pthread_create(&philo[index_p].philosopher, NULL, &dinner_routine, &philo[index_p]);
        index_p++;
    }
    while (index_j < philo->data->number_of_philosophers)
    {
        pthread_join(philo[index_j].philosopher, NULL);
        printf("philo %d encerrou\n", philo[index_j].id);
        index_j++;
    }
}