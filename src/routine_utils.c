/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:26:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/01 13:08:34 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    eating(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        if (philo->fork->fork_status == not_occupied)
            if (pthread_mutex_lock(&philo->fork->fork) != 0)
                return (false);
        philo->fork->fork_status = occupied;
        if (philo->prev->fork->fork_status == not_occupied)
            if (pthread_mutex_lock (&philo->prev->fork->fork) != 0)
                return (false);
        philo->prev->fork->fork_status = occupied;
            
            
    }
    else
    {
        if (philo->prev->fork->fork_status == not_occupied)
            if (pthread_mutex_lock(&philo->prev->fork->fork) != 0)
                return (false);
        philo->prev->fork->fork_status = occupied;
        if (philo->fork->fork_status == not_occupied)
            if (pthread_mutex_lock(&philo->fork->fork) != 0)
                return (false);
        philo->fork->fork_status = occupied;
        safe_printf ("thread is eating", &philo->info->printf_mutex);
    }
}

bool    sleeping(t_philo *philo)
{
    
}

bool    thinking(t_philo *philo)
{
    
}
