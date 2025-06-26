/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:36:19 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/26 15:37:50 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	check_one_philo(t_philo *philo, long time)
/**
 * check_one_philo - Checks if there is only one philo in the simulation.
 * @philo: The philo to check.
 * @time: The current time in milliseconds.
 * @return: true if there is more than one philo, false otherwise.
 */
{
	if (philo->info->num_of_philo == 1)
	{
		pthread_mutex_lock(philo->lfork);
		safe_printf("has taken a fork", &philo->info->printf_mutex, time,
			philo);
		ft_usleep(philo->info->time_to_die * 10, philo);
		philo->state = DIED;
		pthread_mutex_unlock(philo->lfork);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	check_death(t_philo *philo)
/**
 * check_death - Checks if the philo died.
 * @philo: The philo to check.
 * @return: true if the philo died, false otherwise.
 */
{
	long	time;

	time = get_time_in_ms();
	if (time - philo->last_meal > philo->info->time_to_die
		|| philo->state == DIED)
	{
		philo->state = DIED;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_philo_state(t_philo *philo)
/**
 * check_philo_state - Checks if the philo died or the simulation is over.
 * @philo: The philo to check.
 * @return: true if the philo died or the simulation is over, false otherwise.
 */
{
	if ((philo->meals_eaten >= philo->info->num_of_meals
			&& philo->info->num_of_meals != -1)
		|| philo->info->simulation_over == TRUE || philo->state == DIED)
	{
		return (TRUE);
	}
	return (FALSE);
}
