/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:43 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/24 18:10:56 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	take_fork(t_philo *philo, t_fork *fork, long simulation_time)
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
		return (false);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	pthread_mutex_lock(&fork->fork);
	safe_printf("has taken a fork", &philo->info->printf_mutex, time
		- simulation_time, philo->id);
	return (true);
}

t_bool	acquire_forks(t_philo *philo, long simulation_time)
/**
 * acquire_forks - Acquires the forks.
 * @philo: The philo that wants to acquire the forks.
 * @simulation_time: The time when the simulation started.
 * @return: true if the forks were acquired, false otherwise.
 */
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->fork;
		second_fork = philo->prev->fork;
	}
	else
	{
		first_fork = philo->prev->fork;
		second_fork = philo->fork;
	}
	if (!take_fork(philo, first_fork, simulation_time))
		return (false);
	if (!take_fork(philo, second_fork, simulation_time))
	{
		pthread_mutex_unlock(&first_fork->fork);
		return (false);
	}
	return (true);
}

void	release_forks(t_philo *philo)
/**
 * release_forks - Releases the forks.
 * @philo: The philo that wants to release the forks.
 */
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->fork;
		second_fork = philo->prev->fork;
	}
	else
	{
		first_fork = philo->prev->fork;
		second_fork = philo->fork;
	}
	pthread_mutex_unlock(&first_fork->fork);
	pthread_mutex_unlock(&second_fork->fork);
}
