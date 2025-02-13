/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:36:19 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/11 08:58:54 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	change_statement(t_philo *philo)
/**
 * change_statement - Changes the state of the philo to died.
 * @philo: The philo to change its state.
 */
{
	t_philo	*node;

	if (!philo)
		return ;
	node = philo;
	while (1)
	{
		node->state = died;
		node = node->next;
		if (node == philo)
			break ;
	}
}

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
		pthread_mutex_unlock(&philo->info->death_mutex);
		pthread_mutex_lock(&philo->fork->fork);
		safe_printf("has taken a fork", &philo->info->printf_mutex, time - time,
			philo->id);
		ft_usleep(philo->info->time_to_die);
		safe_printf("died", &philo->info->printf_mutex, get_time_in_ms() - time,
			philo->id);
		pthread_mutex_unlock(&philo->fork->fork);
		return (false);
	}
	return (true);
}

t_bool	check_death(t_philo *philo)
/**
 * check_death - Checks if the philo died.
 * @philo: The philo to check.
 * @return: true if the philo died, false otherwise.
 */
{
	long	time;

	pthread_mutex_lock(&philo->info->simulation_mutex);
	time = get_time_in_ms();
	if (philo->last_meal == 0)
	{
		pthread_mutex_unlock(&philo->info->simulation_mutex);
		return (false);
	}
	if (time - philo->last_meal >= philo->info->time_to_die
		|| philo->state == died || philo->info->simulation_over == true)
	{
		philo->state = died;
		philo->info->simulation_over = true;
		pthread_mutex_unlock(&philo->info->simulation_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->simulation_mutex);
	return (false);
}

t_bool	check_philo_state(t_philo *philo)
/**
 * check_philo_state - Checks if the philo died or the simulation is over.
 * @philo: The philo to check.
 * @return: true if the philo died or the simulation is over, false otherwise.
 */
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if ((philo->meals_eaten >= philo->info->num_of_meals
			&& philo->info->num_of_meals != -1))
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	if (philo->state == died || philo->info->simulation_over == true)
	{
		pthread_mutex_lock(&philo->info->simulation_mutex);
		change_statement(philo);
		pthread_mutex_unlock(&philo->info->simulation_mutex);
		philo->info->simulation_over = true;
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (false);
}
