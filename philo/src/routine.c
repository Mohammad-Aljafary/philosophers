/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/25 13:16:32 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_usleep(long long time_in_ms, t_philo *philo)
/**
 * ft_usleep - Sleeps for a given amount of time.
 * @time_in_ms: The time to sleep in milliseconds.
 */
{
	long long	start_time;

	(void)philo;
	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < time_in_ms)
	{
		if (check_death(philo))
			return (FALSE);
		usleep(1);
	}
	return (TRUE);
}

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
	printf("%s%ld %s%d %s%s\n%s", YELLOW, get_time_in_ms() - current_time, GREEN, id, RED, msg,
		RESET);
	pthread_mutex_unlock(printf_mutex);
}

void	print_died(t_philo *philo, long time)
/**
 * print_died - Prints the died message.
 */
{
	static int	printt = 0;

	if (philo->state == DIED && printt == 0)
	{
		safe_printf("died", &philo->info->printf_mutex, time, philo->id);
		printt = 1;
	}
}

 t_bool	routine_2(t_philo *philo, long time)
 /*
 * routine_2 - The routine of the philo.
 * @philo: The philo to run the routine.
 * @time: The time when the simulation started.
 * @return: true if the philo finished the routine, false otherwise.*/
{
	if (check_philo_state(philo))
		return (FALSE);
	if (!acquire_forks(philo, time))
		return (FALSE);
	if (!eating_thread(philo, time))
	{
		release_forks(philo);
		return (FALSE);
	}
	release_forks(philo);
	if (!sleeping_thread(philo, time))
		return (FALSE);
	if (!thinking_thread(philo, time))
		return (FALSE);
	return (TRUE);
}

void	*routine(void *arg)
/**
 * routine - The routine of the philo.
 * @arg: The philo to run the routine.
 * @return: NULL.
 */
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!check_one_philo(philo, philo->info->start_time))
		return (NULL);
 	while (1)
	{
		if (!routine_2(philo, philo->info->start_time))
			break ;
	}
	pthread_mutex_lock(&philo->info->death_mutex);
	print_died(philo, philo->info->start_time);
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (NULL);
}
