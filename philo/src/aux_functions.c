/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:58:33 by marvin            #+#    #+#             */
/*   Updated: 2024/07/24 20:58:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long int	ft_atoli(const char *nptr)
{
	long int	result;

	result = 0;
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		result *= 10;
		result += *nptr - '0';
		nptr++;
	}
	return (result);
}
