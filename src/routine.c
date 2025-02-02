/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/02 14:27:05 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
    * safe_printf - Prints a message to the standard output.
    * @msg: The message to be printed.
    * @printf_mutex: The mutex that locks the standard output.
    * due to the data races caused by the threads when they write to the standard output. 
 */
void    safe_printf(const char *msg, pthread_mutex_t *printf_mutex)
{
    pthread_mutex_lock(printf_mutex);
    printf("%s%s\n %s", YELLOW, msg, RESET);
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
        if (next_node == philo)
            return (true);
        if (ptr->state == died)
            return (false);
        ptr = ptr->next;
        next_node = next_node->next;
    }
    return (true);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        eating_thread(philo);
        pthread_mutex_lock(&philo->lock);
        usleep(1000);
        pthread_mutex_unlock(&philo->lock);
        thinking_thread(philo);
        //sleeping(philo); 
    }
    return NULL;
}
