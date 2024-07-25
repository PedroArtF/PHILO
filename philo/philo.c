/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:30:24 by marvin            #+#    #+#             */
/*   Updated: 2024/07/23 16:30:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_philo         *philo;

    if (args_validation(argc, argv))
        return (EXIT_FAILURE);
    philo = initializing_philo(argv);
    printf("%ld e %ld\n", philo->data->number_of_philosophers, philo->data->time_to_sleep);
    //(void)philo;
    return (EXIT_SUCCESS);
}