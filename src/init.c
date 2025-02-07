/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:17 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/07 07:49:02 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    init_mutex(t_fork **fork, t_info *info)
{
    if (fork == NULL || *fork == NULL)
        return (false);
    if (pthread_mutex_init(&(*fork)->fork, NULL) != 0)
        return (false);
    if (pthread_mutex_init(&info->death_mutex, NULL))
        return (false);
    return (true);
}
