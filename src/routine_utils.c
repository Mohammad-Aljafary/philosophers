/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/03 14:34:36 by malja-fa         ###   ########.fr       */
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
    if (!check_if_died(philo))
        return (false);
    pthread_mutex_lock(&first_fork->fork);
    pthread_mutex_lock(&second_fork->fork);
    printf("%d Thread is eating\n", philo->id);
    safe_printf("Thread is eating", &philo->info->printf_mutex);
    philo->state = eating;
    usleep(philo->info->time_to_eat);
    pthread_mutex_unlock(&first_fork->fork);
    pthread_mutex_unlock(&second_fork->fork);
    return (true);
}


 bool    sleeping_thread(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock);
    philo->state = sleeping;
    safe_printf("Thread is sleeping", &philo->info->printf_mutex);
    usleep(philo->info->time_to_sleep);
    pthread_mutex_unlock(&philo->lock);
    return (true);
}

bool    thinking_thread(t_philo *philo)
{
    pthread_mutex_lock(&philo->lock);
    philo->state = thinking;
    safe_printf("Thread is thinking", &philo->info->printf_mutex);
    //usleep();
    pthread_mutex_unlock(&philo->lock);
    return (true);
}
