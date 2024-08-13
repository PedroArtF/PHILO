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

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

void	ft_putstr_fd(const char *string, int fd)
{
	if (!string)
		return ;
	write(fd, string, ft_strlen(string));
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

char	*format_string(const char *s, const char *s1, const char *s2, const char *s3)
{
	int		lenght;
	int		index;
	char	*formatted_string;

	lenght = (ft_strlen(s) + ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	formatted_string = malloc((lenght + 1) * sizeof(char));
	formatted_string[lenght] = '\0';
	lenght = 0;
	index = 0;
	while (s[index])
		formatted_string[lenght++] = s[index++];
	index = 0;
	while (s1[index])
		formatted_string[lenght++] = s1[index++];
	index = 0;
	while (s2[index])
		formatted_string[lenght++] = s2[index++];
	index = 0;
	while (s3[index])
		formatted_string[lenght++] = s3[index++];
	return (formatted_string);
}

