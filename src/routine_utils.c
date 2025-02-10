/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/10 08:17:06 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_usleep(long long time_in_ms)
{
	long long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_in_ms)
		usleep(10);
}

t_bool	eating_thread(t_philo *philo, long simulation_time)
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
