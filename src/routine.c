/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/09 09:36:02 by malja-fa         ###   ########.fr       */
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
	printf("%s%ld %s%d %s%s\n %s", YELLOW, current_time, GREEN, id, BLUE, msg, RESET);
	pthread_mutex_unlock(printf_mutex);
}

void	change_statement(t_philo *philo)
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

t_bool	check_death(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->info->simulation_mutex);
	time = get_time_in_ms();
	if (philo->last_meal == 0)
		philo->last_meal = time;
	if (time - philo->last_meal >= philo->info->time_to_die || philo->state == died 
		|| philo->info->simulation_over == true)
	{
		/* pthread_mutex_unlock(&philo->info->death_mutex);
		pthread_mutex_lock(&philo->info->death_mutex);*/
		//change_statement(philo);
		philo->state = died;
		philo->info->simulation_over = true;
		pthread_mutex_unlock(&philo->info->simulation_mutex); 
		return (true);
	}
	pthread_mutex_unlock(&philo->info->simulation_mutex); 
	return (false);
}

t_bool	check_philo_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if ((philo->meals_eaten >= philo->info->num_of_meals
			&& philo->info->num_of_meals != -1) || philo->state == died
			|| philo->info->simulation_over == true)
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

void *routine(void *arg)
{
    t_philo *philo;
    long time;
    //static int printt = 0;  // Static variable to ensure the "died" message is printed only once

    philo = (t_philo *)arg;
    time = get_time_in_ms();
    while (1)
    {
        pthread_mutex_lock(&philo->info->death_mutex);
        if (philo->info->simulation_over)
        {
            pthread_mutex_unlock(&philo->info->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->info->death_mutex);
        if (check_philo_state(philo))
            break;
        if (!thinking_thread(philo, time))
			break;
		if (!acquire_forks(philo, time))
			break;
		if (!eating_thread(philo, time))
		{
			release_forks(philo);
			break;
		}
		release_forks(philo);
       if (philo->state == died)
            break;
        if (!sleeping_thread(philo, time))
			break;
        if (philo->state == died)
            break;
    }
	safe_printf ("died", &philo->info->printf_mutex, get_time_in_ms(), philo->id);
    return NULL;
}
