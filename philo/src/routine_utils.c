/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/19 08:01:08 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_usleep(long long time_in_ms)
/**
 * ft_usleep - Sleeps for a given amount of time.
 * @time_in_ms: The time to sleep in milliseconds.
 */
{
	long long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_in_ms)
		usleep(5);
}

t_bool	eating_thread(t_philo *philo, long simulation_time)
/**
 * eating_thread - The eating thread routine.
 * @philo: The philo that wants to eat.
 * @simulation_time: The time when the simulation started.
 * @return: true if the philo ate, false otherwise.
 */
{
	long	time;

	time = get_time_in_ms();
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_death(philo) || philo->info->simulation_over == true)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	safe_printf("is eating", &philo->info->printf_mutex, time - simulation_time,
		philo->id);
	philo->last_meal = time;
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->death_mutex);
	ft_usleep(philo->info->time_to_eat);
	return (true);
}

t_bool	sleeping_thread(t_philo *philo, long simulation_time)
/**
 * sleeping_thread - The sleeping thread routine.
 * @philo: The philo that wants to sleep.
 * @simulation_time: The time when the simulation started.
 * @return: true if the philo slept, false otherwise.
 */
{
	long	time;

	time = get_time_in_ms();
	if (check_philo_state(philo))
		return (false);
	pthread_mutex_lock(&philo->lock);
	philo->state = sleeping;
	safe_printf("is sleeping", &philo->info->printf_mutex, time
		- simulation_time, philo->id);
	ft_usleep(philo->info->time_to_sleep);
	pthread_mutex_unlock(&philo->lock);
	return (true);
}

t_bool	thinking_thread(t_philo *philo, long simulation_time)
/**
 * thinking_thread - The thinking thread routine.
 * @philo: The philo that wants to think.
 * @simulation_time: The time when the simulation started.
 * @return: true if the philo thought, false otherwise.
 */
{
	long	time;

	time = get_time_in_ms();
	if (check_philo_state(philo))
		return (false);
	pthread_mutex_lock(&philo->lock);
	philo->state = thinking;
	safe_printf("is thinking", &philo->info->printf_mutex, time
		- simulation_time, philo->id);
	ft_usleep(200);
	pthread_mutex_unlock(&philo->lock);
	return (true);
}
