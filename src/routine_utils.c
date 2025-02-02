/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/02 14:28:54 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool eating_thread(t_philo *philo)
{
    t_fork *first_fork;
    t_fork *second_fork;

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
    pthread_mutex_lock(&first_fork->fork);
    first_fork->fork_status = occupied;
    pthread_mutex_lock(&second_fork->fork);
    second_fork->fork_status = occupied;
    safe_printf("Thread is eating", &philo->info->printf_mutex);
    philo->state = eating;
    first_fork->fork_status = not_occupied;
    pthread_mutex_unlock(&first_fork->fork);
    second_fork->fork_status = not_occupied;
    pthread_mutex_unlock(&second_fork->fork);
    return (true);
}


/* bool    sleeping(t_philo *philo)
{
    
}*/

bool    thinking_thread(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock);
    philo->state = thinking;
    safe_printf("Thread is thinking", &philo->info->printf_mutex);
    usleep(1000);
    pthread_mutex_unlock(&philo->lock);
    return (true);
}
