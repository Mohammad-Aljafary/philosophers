/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:52:03 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/26 15:54:30 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_num_of_meals(t_philo *philo)
/**
 * this func is to check that every philo
 * has eaten the number of meals required 
 * @return: 0 when the philos have not eaten the 
 * 			number of meals
 * 			1 when they all have eaten the meals
 */
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (i < philo->info->num_of_philo)
	{
		if ((philo[i].meals_eaten >= philo->info->num_of_meals) 
			&& philo->info->num_of_meals != -1)
			num++;
		i++;
	}
	if (num ==  philo->info->num_of_philo)
		return (1);
	return (0);
}

static int	monitor_philo(t_philo *philo, int i)
/**
 * @philo: the philosophers to check
 * @i: the index of the philos
 * @return: 1 when one philo die or it reached the condition when 
 * 			the simulation of the philos to stop
 * 			0 when none of the conditions is reached
 */
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if (check_death(philo + i))
	{
		philo->info->simulation_over = TRUE;
		pthread_mutex_unlock(&philo->info->death_mutex);
		safe_printf("died", &philo->info->printf_mutex,
			philo->info->start_time, philo + i);
		return (1);
	}
	if (check_philo_state(philo + i) && check_num_of_meals(philo))
	{
		philo->info->simulation_over = TRUE;
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (0);
}

void	*monitor_routine(void *philos)
/**
 * @philos: is the philosophers to check if they are dead or not
 * the main purpose is stop the simulation when one philo die
 * @return: NULL to stop the monitor when philo dies
 */
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philos;
	i = 0;
	while (1)
	{
		if (i == philo->info->num_of_philo)
			i = 0;
		if (monitor_philo(philo, i))
			return (NULL);
		usleep(100);
		i++;
	}
	return (NULL);
}
