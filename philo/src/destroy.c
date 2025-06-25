/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:59:41 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/25 14:44:00 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_info(t_info *info)
{
	int i;
	
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
	free (*philos);
}

void change_statement(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->num_of_philo)
	{
		if (philo[i].state != DIED)
		{
			philo[i].state = DIED;
		}
		philo[i].info->simulation_over = TRUE;
		i++;
	}
}