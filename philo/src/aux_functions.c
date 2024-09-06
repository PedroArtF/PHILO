/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parthur- <parthur-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:24:08 by parthur-          #+#    #+#             */
/*   Updated: 2024/08/30 20:24:08 by parthur-         ###   ########.fr       */
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

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

int	ft_strlen(const char *string)
{
	int	counter;

	counter = 0;
	if (!string)
		return (counter);
	while (string[counter])
		counter++;
	return (counter);
}

static long int	long_int_lenght(long int num)
{
	long int	lenght;

	lenght = 0;
	if (num <= 0)
		lenght += 1;
	while (num != 0)
	{
		lenght++;
		num = num / 10;
	}
	lenght++;
	return (lenght);
}

char	*ft_litoa(long int num)
{
	long int	iterator;
	long int	alloc;
	char		*string;

	alloc = long_int_lenght(num);
	iterator = alloc - 1;
	string = malloc(alloc * sizeof(char));
	if (!string)
		return (malloc(0));
	if (num == 0)
		string[0] = '0';
	if (num < 0)
	{
		num *= -1;
		string[0] = '-';
	}
	string[iterator] = '\0';
	while (iterator--, num != 0)
	{
		string[iterator] = num % 10 + '0';
		num = num / 10;
	}
	return (string);
}
