/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:17 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/25 13:03:15 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	init_philos(t_info *info, t_philo **philos)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * info->num_of_philo);
	if (!*philos)
		return (FALSE);
	i = -1;
	while (++i < info->num_of_philo)
	{
		(*philos)[i].state = NORM;
		(*philos)[i].id = i + 1;
		(*philos)[i].info = info;
		(*philos)[i].last_meal = 0;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].lfork = &info->fork[i];
		if (i == info->num_of_philo - 1)
			(*philos)[i].rfork = &info->fork[0];
		else
			(*philos)[i].rfork = &info->fork[i + 1];
	}
	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_create(&(*philos)[i].philo, NULL, routine, &(*philos)[i]))
		{
			while (--i >= 0)
				pthread_join((*philos)[i].philo, NULL);
			free(*philos);
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool	init_forks(t_info *info)
{
	int	i;

	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->fork)
			return (FALSE);
	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&info->fork[i]);
			free(info->fork);
			return (FALSE);
		}
	}
	return (TRUE);
}
