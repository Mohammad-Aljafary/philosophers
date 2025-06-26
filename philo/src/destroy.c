/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:59:41 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/26 15:56:07 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_info(t_info *info)
/**
 * @info: the struct to free
 */
{
	int	i;

	if (info)
	{
		pthread_mutex_destroy(&info->death_mutex);
		pthread_mutex_destroy(&info->printf_mutex);
		if (info->fork)
		{
			i = 0;
			while (i < info->num_of_philo)
			{
				pthread_mutex_destroy(&info->fork[i]);
				i++;
			}
		}
		free(info->fork);
		free(info);
	}
}

void	join_threads(t_info *info, t_philo **philos)
/**
 * join_threads - Joins the threads.
 * @info: The info struct that contains the data to be passed to the threads.
 * @thread: A pointer to the head of the list.
 * @return: 1 if an error occurs, 0 otherwise.
 */
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join((*philos)[i].philo, NULL);
		i++;
	}
	free(*philos);
}

