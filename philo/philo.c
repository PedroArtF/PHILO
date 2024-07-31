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
    if (!(philo = initializing_philo(argv)))
        return (EXIT_FAILURE);
    start_simulation(philo);
    return (EXIT_SUCCESS);
}