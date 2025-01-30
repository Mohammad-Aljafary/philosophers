/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:17 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:47 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    init_mutex(t_fork **fork)
{
    if (pthread_mutex_init(&(*fork)->fork, NULL) != 0)
        return (false);
    (*fork)->fork_status = not_occupied;
    return (true);
}
