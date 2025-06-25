/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:52:03 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/25 17:56:05 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    *monitor_routine(void *philos)
{
    t_philo *philo;
    int     i;

    philo = (t_philo *)philos;
    i = 0;
    while (1)
    {
        if (i == philo->info->num_of_philo)
            i = 0;
        pthread_mutex_lock(&philo->info->death_mutex);
        if (check_death(philo + i))
        {
            philo->info->simulation_over = TRUE;
            pthread_mutex_unlock(&philo->info->death_mutex);
            safe_printf("died", &philo->info->printf_mutex, philo->info->start_time, philo + i);
            return (NULL);
        }
        if (check_philo_state(philo + i))
        {
            philo->info->simulation_over = TRUE;
            pthread_mutex_unlock(&philo->info->death_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->info->death_mutex);
        usleep(100);
        i++;
    }
    return (NULL);
}
