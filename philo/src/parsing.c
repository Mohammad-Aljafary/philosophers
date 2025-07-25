/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:11:39 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/26 15:47:23 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	parse_atoi(char *str)
/**
 * parse_atoi - Parses a string to an integer.
 * @str: The string to be parsed.
 * @return: The integer value of the string.
 */
{
	long long	result;

	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > 2147483647)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (result);
}

long	get_time_in_ms(void)
/**
 * this func to get the current time 
 * when it is called
 */
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("gettimeofday");
		return (-1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
