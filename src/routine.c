/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/07 10:00:44 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
    * safe_printf - Prints a message to the standard output.
    * @msg: The message to be printed.
    * @printf_mutex: The mutex that locks the standard output.
    * due to the data races caused by the threads when they write to the standard output. 
 */
void    safe_printf(const char *msg, pthread_mutex_t *printf_mutex, long current_time, int id)
{
    pthread_mutex_lock(printf_mutex);
    printf("%ld %d %s%s\n %s", current_time, id, BLUE, msg, RESET);
    pthread_mutex_unlock(printf_mutex);  
}

bool    check_if_died(t_philo *philo)
{
    t_philo *ptr;
    t_philo *next_node;
    ptr = philo;
    next_node = ptr->next; 
    while (ptr)
    {
        if(check_death(&next_node))
            return (false);
        if (next_node == philo)
            return (true);
        if (ptr->state == died)
            return (false);
        ptr = ptr->next;
        next_node = next_node->next;
    }
    return (true);
}

bool    check_death(t_philo **philo)
{
    long    time;

    time = get_time_in_ms();
    if (time - (*philo)->last_meal >= (*philo)->info->time_to_die)
    {
        (*philo)->state = died;
        return (true);
    }
    return (false);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    long    time;

    time = get_time_in_ms();
    while (1)
    {
        if ((philo->meals_eaten >= philo->info->num_of_meals) && philo->info->num_of_meals != -1)
            break;
        thinking_thread(philo, time);
        sleeping_thread(philo, time);
        eating_thread(philo, time);
    }
    
    return (NULL);
}


