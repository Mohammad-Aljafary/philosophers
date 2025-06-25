/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/25 14:33:41 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	if (check_death(philo) || check_philo_state(philo))
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	safe_printf("is eating", &philo->info->printf_mutex, simulation_time,
		philo->id);
	philo->last_meal = time;
	philo->meals_eaten++;
	philo->state = EATING;
	if (!ft_usleep(philo->info->time_to_eat, philo))
		return (FALSE);
	return (TRUE);
}

t_bool	sleeping_thread(t_philo *philo, long simulation_time)
/**
 * sleeping_thread - The sleeping thread routine.
 * @philo: The philo that wants to sleep.
 * @simulation_time: The time when the simulation started.
 * @return: true if the philo slept, false otherwise.
 */
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_philo_state(philo))
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	philo->state = SLEEPING;
	safe_printf("is sleeping", &philo->info->printf_mutex, simulation_time, philo->id);
	if (!ft_usleep(philo->info->time_to_sleep, philo))
		return (FALSE);
	return (TRUE);
}

t_bool	thinking_thread(t_philo *philo, long simulation_time)
/**
 * thinking_thread - The thinking thread routine.
 * @philo: The philo that wants to think.
 * @simulation_time: The time when the simulation started.
 * @return: true if the philo thought, false otherwise.
 */
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_philo_state(philo))
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	philo->state = THINKING;
	safe_printf("is thinking", &philo->info->printf_mutex, simulation_time, philo->id);
	ft_usleep(5, philo);
	return (TRUE);
}
