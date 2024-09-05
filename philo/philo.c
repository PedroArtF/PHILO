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

int	main(int argc, char **argv)
{
	t_dinner_manager		*manager;

	if (args_validation(argc, argv))
		return (EXIT_FAILURE);
	manager = initializing_manager(argv);
	if (!manager)
		return (EXIT_FAILURE);
	start_simulation(manager);
	return (EXIT_SUCCESS);
}
