/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:15:43 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/10 08:17:42 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	take_fork(t_philo *philo, t_fork *fork, long simulation_time)
{
	long	time;

	time = get_time_in_ms();
	pthread_mutex_lock(&fork->fork);
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_death(philo) || (philo->meals_eaten >= philo->info->num_of_meals
			&& philo->info->num_of_meals != -1) || philo->state == died
		|| philo->info->simulation_over == true)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		pthread_mutex_unlock(&fork->fork);
		return (false);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
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
