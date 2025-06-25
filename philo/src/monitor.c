/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:52:03 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/25 10:26:47 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void    *monitor_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    while (1)
    {
        pthread_mutex_lock(&philo->info->death_mutex);
        if (check_death(philo) || check_philo_state(philo))
        {
            philo->info->simulation_over = TRUE;
            pthread_mutex_unlock(&philo->info->death_mutex);
            return (NULL);
        }
        usleep (5);
        pthread_mutex_unlock(&philo->info->death_mutex);
    }
    return (NULL);
}
