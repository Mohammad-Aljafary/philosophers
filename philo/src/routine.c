/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/04/14 08:59:38 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	safe_printf(const char *msg, pthread_mutex_t *printf_mutex,
		long current_time, int id)
/**
 * safe_printf - Prints a message to the standard output.
 * @msg: The message to be printed.
 * @printf_mutex: The mutex that locks the standard output.

	* due to the data races caused by the threads when they write to the standard output.
 */
{
	pthread_mutex_lock(printf_mutex);
	printf("%s%ld %s%d %s%s\n%s", YELLOW, current_time, GREEN, id, RED, msg,
		RESET);
	pthread_mutex_unlock(printf_mutex);
}

void	print_died(t_philo *philo, long time)
/**
 * print_died - Prints the died message.
 */
{
	static int	printt = 0;

	if (philo->state == died && printt == 0)
	{
		safe_printf("died", &philo->info->printf_mutex, get_time_in_ms()
			- time, philo->id);
		printt = 1;
	}
}

t_bool	routine_2(t_philo *philo, long time)
/**
 * routine_2 - The routine of the philo.
 * @philo: The philo to run the routine.
 * @time: The time when the simulation started.
 * @return: true if the philo finished the routine, false otherwise.
 */
{
	if (check_philo_state(philo))
		return (false);
	if (!thinking_thread(philo, time))
		return (false);
	if (!acquire_forks(philo, time))
		return (false);
	if (!eating_thread(philo, time))
	{
		release_forks(philo);
		return (false);
	}
	release_forks(philo);
	if (!sleeping_thread(philo, time))
		return (false);
	return (true);
}

void	*routine(void *arg)
/**
 * routine - The routine of the philo.
 * @arg: The philo to run the routine.
 * @return: NULL.
 */
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	time = get_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->info->death_mutex);
		if (philo->info->simulation_over)
		{
			pthread_mutex_unlock(&philo->info->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->death_mutex);
		pthread_mutex_lock(&philo->info->death_mutex);
		if (!check_one_philo(philo, time))
			return (NULL);
		pthread_mutex_unlock(&philo->info->death_mutex);
		if (!routine_2(philo, time))
			break ;
	}
	pthread_mutex_lock(&philo->info->death_mutex);
	print_died(philo, time);
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (NULL);
}
