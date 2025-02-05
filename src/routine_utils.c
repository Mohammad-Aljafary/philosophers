/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/05 12:34:59 by malja-fa         ###   ########.fr       */
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
    safe_printf("has taken a fork", &philo->info->printf_mutex, get_time_in_ms(), philo->id);
    pthread_mutex_lock(&second_fork->fork);
    safe_printf("has taken a fork", &philo->info->printf_mutex, get_time_in_ms(), philo->id);
    safe_printf("is eating", &philo->info->printf_mutex, get_time_in_ms(), philo->id);
    philo->state = eating;
    philo->last_meal = get_time_in_ms();
    usleep(philo->info->time_to_eat * 100);
    pthread_mutex_unlock(&first_fork->fork);
    pthread_mutex_unlock(&second_fork->fork);
    return (true);
}


 bool    sleeping_thread(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock);
    philo->state = sleeping;
    safe_printf("is sleeping", &philo->info->printf_mutex, get_time_in_ms(), philo->id);
    usleep(philo->info->time_to_sleep * 100);
    pthread_mutex_unlock(&philo->lock);
    return (true);
}

bool    thinking_thread(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock);
    philo->state = thinking;
    safe_printf("is thinking", &philo->info->printf_mutex, get_time_in_ms(), philo->id);
    usleep(10000);
    pthread_mutex_unlock(&philo->lock);
    return (true);
}
