/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:17 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/30 13:39:22 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    init_mutex(t_fork **fork,t_info *info)
{
    int i;

    i = 0;
    (*fork)->fork = malloc(info->num_of_philo * sizeof(pthread_mutex_t));
    if (!(*fork)->fork)
        return (false);
    (*fork)->fork_status = malloc(info->num_of_philo * sizeof(int));
    while (i < info->num_of_philo)
    {
        if (pthread_mutex_init(&(*fork)->fork[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&(*fork)->fork[i]);
            return (false);
        }
        (*fork)->fork_status = not_occupied;
        i++;
    }
    return (true);
}
