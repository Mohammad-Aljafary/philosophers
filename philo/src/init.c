/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:17 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/24 21:06:01 by malja-fa         ###   ########.fr       */
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
		(*philos)[i].id = i;
		(*philos)[i].info = info;
		(*philos)[i].last_meal = 0;
		(*philos)[i].meals_eaten = 0;
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
