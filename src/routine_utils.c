/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/08 12:33:49 by malja-fa         ###   ########.fr       */
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

t_bool	take_fork(t_philo *philo, t_fork *fork, long simulation_time)
{
	long	time;

	time = get_time_in_ms();
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_death(philo) || philo->state == died)
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

t_bool	eating_thread(t_philo *philo, long simulation_time)
{
	long	time;

	time = get_time_in_ms();
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_death(philo) || philo->state == died)
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

void	release_forks(t_philo *philo)
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

t_bool	sleeping_thread(t_philo *philo, long simulation_time)
{
	long	time;

	time = get_time_in_ms();
	pthread_mutex_lock(&philo->lock);
	if (check_philo_state(philo))
	{	
		pthread_mutex_unlock(&philo->lock);
		return (false);	
	}
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
	pthread_mutex_lock(&philo->lock);
	if (check_philo_state(philo))
    {
		pthread_mutex_unlock(&philo->lock);
		return (false);	
	}
	philo->state = thinking;
	safe_printf("is thinking", &philo->info->printf_mutex, time
		- simulation_time, philo->id);
	ft_usleep(100);
	pthread_mutex_unlock(&philo->lock);
	return (true);
}
