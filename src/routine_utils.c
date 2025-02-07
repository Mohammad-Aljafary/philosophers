/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/07 09:59:28 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_usleep(long long time_in_ms)
{
    long long start_time = get_time_in_ms();
    
    while ((get_time_in_ms() - start_time) < time_in_ms)
        ;
}      


bool eating_thread(t_philo *philo, long simulation_time)
{
    t_fork *first_fork;
    t_fork *second_fork;
    long    time;

    time = get_time_in_ms();
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
    safe_printf("has taken a fork", &philo->info->printf_mutex, time - simulation_time, philo->id);
    pthread_mutex_lock(&second_fork->fork);
    safe_printf("has taken a fork", &philo->info->printf_mutex, time - simulation_time, philo->id);
    safe_printf("is eating", &philo->info->printf_mutex, time - simulation_time, philo->id);
    philo->state = eating;
    philo->last_meal = get_time_in_ms();
    philo->meals_eaten++;
    ft_usleep(philo->info->time_to_eat);
    pthread_mutex_unlock(&first_fork->fork);
    pthread_mutex_unlock(&second_fork->fork);
    return (true);
}

bool    sleeping_thread(t_philo *philo, long simulation_time)
{
    long    time;

    time = get_time_in_ms();
    pthread_mutex_lock(&philo->lock);
    philo->state = sleeping;
    safe_printf("is sleeping", &philo->info->printf_mutex, time - simulation_time, philo->id);
    ft_usleep(philo->info->time_to_sleep);
    pthread_mutex_unlock(&philo->lock);
    return (true);
}

bool    thinking_thread(t_philo *philo, long simulation_time)
{
    long    time;

    time = get_time_in_ms();
    pthread_mutex_lock(&philo->lock);
    philo->state = thinking;
    safe_printf("is thinking", &philo->info->printf_mutex, time - simulation_time, philo->id);
    ft_usleep(10);
    pthread_mutex_unlock(&philo->lock);
    return (true);
}
