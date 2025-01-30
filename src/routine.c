/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:12:06 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/30 13:28:35 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

pthread_mutex_t print_mutex;

void safe_printf(const char *msg)
{
    pthread_mutex_lock(&print_mutex);
    printf("%s\n", msg);
    pthread_mutex_unlock(&print_mutex);
}

void *monitor_check(void *arg)
{  
    (void)arg;
    safe_printf("BOOMMM");
    return (NULL);
}

void *routine(void *arg)
{
    (void)arg;  
    safe_printf("hiiiiiii");
    return (NULL);
}

