/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:43 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/25 09:25:53 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	take_fork(t_philo *philo, pthread_mutex_t *fork, long simulation_time)
/**
 * take_fork - Tries to take a fork.
 * @philo: The philo that wants to take the fork.
 * @fork: The fork to take.
 * @simulation_time: The time when the simulation started.
 * @return: true if the fork was taken, false otherwise.

 */
{
	long	time;

	time = get_time_in_ms();
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_death(philo) || check_philo_state(philo))
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	pthread_mutex_lock(fork);
	safe_printf("has taken a fork", &philo->info->printf_mutex, time
		- simulation_time, philo->id);
	return (TRUE);
}

t_bool	acquire_forks(t_philo *philo, long simulation_time)
/**
 * acquire_forks - Acquires the forks.
 * @philo: The philo that wants to acquire the forks.
 * @simulation_time: The time when the simulation started.
 * @return: true if the forks were acquired, false otherwise.
 */
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	
	if (philo->id % 2 == 0)
	{
		first_fork = philo->lfork;
		second_fork = philo->rfork;
	}
	else
	{
		first_fork = philo->rfork;
		second_fork = philo->lfork;
	}
	if (!take_fork(philo, first_fork, simulation_time))
		return (FALSE);
	if (!take_fork(philo, second_fork, simulation_time))
	{
		pthread_mutex_unlock(first_fork);
		return (FALSE);
	}
	return (TRUE);
}

void	release_forks(t_philo *philo)
/**
 * release_forks - Releases the forks.
 * @philo: The philo that wants to release the forks.
 */
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->lfork;
		second_fork = philo->rfork;
	}
	else
	{
		first_fork = philo->rfork;
		second_fork = philo->lfork;
	}
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}
