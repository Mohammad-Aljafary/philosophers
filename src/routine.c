/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/07 14:02:29 by malja-fa         ###   ########.fr       */
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
	printf("%ld %d %s%s\n %s", current_time, id, BLUE, msg, RESET);
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

	time = get_time_in_ms();
	if (philo->last_meal == 0)
		philo->last_meal = time;
	if (time - philo->last_meal >= philo->info->time_to_die)
	{
		philo->state = died;
		return (true);
	}
	return (false);
}   

t_bool  check_philo_state(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->death_mutex);

    if ((philo->meals_eaten >= philo->info->num_of_meals
            && philo->info->num_of_meals != -1) || philo->state == died)
    {
        pthread_mutex_unlock(&philo->info->death_mutex);
        return (true);
    }

    pthread_mutex_unlock(&philo->info->death_mutex);
    return (false);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long time = get_time_in_ms();

    while (1)
    {
        if (check_philo_state(philo))
            break;
        thinking_thread(philo, time);
        if (check_philo_state(philo)) 
            break;
        sleeping_thread(philo, time);
        if (check_philo_state(philo))
            break;
        if (!eating_thread(philo, time))
            break;
    }

    return NULL;
}
