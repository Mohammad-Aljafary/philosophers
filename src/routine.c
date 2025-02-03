/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/03 15:03:08 by malja-fa         ###   ########.fr       */
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
    printf("%s%s\n %s", BLUE, msg, RESET);
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

long get_current_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        // Check if the simulation should stop
        pthread_mutex_lock(&philo->info->death_mutex);
        if (philo->info->simulation_over)
        {
            pthread_mutex_unlock(&philo->info->death_mutex);
            return NULL; // Exit thread
        }
        pthread_mutex_unlock(&philo->info->death_mutex);

        // Check if the philosopher has died
        if (get_time_in_ms() - philo->last_meal >= philo->info->time_to_die)
        {
            pthread_mutex_lock(&philo->info->death_mutex);
            philo->info->simulation_over = true; // Stop all threads
            printf("%ld\n", get_time_in_ms() - philo->last_meal );
            printf("%ld\n", philo->info->time_to_die);
            pthread_mutex_unlock(&philo->info->death_mutex);

            safe_printf("Philosopher has died.\n", &philo->info->printf_mutex);
            return NULL; // Exit thread
        }

        // Eating phase
        if (!eating_thread(philo))
            return NULL; // If eating failed, philosopher dies

        // Update last meal time
        philo->last_meal =  get_time_in_ms();

        // Thinking phase
        thinking_thread(philo);

        // Sleeping phase
        sleeping_thread(philo);
    }

    return NULL;
}

