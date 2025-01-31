/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/31 23:01:54 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void safe_printf(const char *msg, pthread_mutex_t *printf_mutex)
{
    pthread_mutex_lock(printf_mutex);
    printf("%s%s\n %s", YELLOW, msg, RESET);
    pthread_mutex_unlock(printf_mutex);  
}

void *monitor_check(void *arg)
{  
    t_monitor *monitor;

    monitor= (t_monitor *)arg;
    printf("%d\n", monitor->philo->id);
    safe_printf("BOOMMM", &monitor->philo->info->printf_mutex);
    return (NULL);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    printf("id: %d\n", philo->id);
    safe_printf("BOOMMM", &philo->info->printf_mutex);
    return (NULL);
}

