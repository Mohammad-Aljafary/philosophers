/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:55:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/24 15:13:19 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum
{
    false,
    true    
}   bool;

typedef struct s_philo
{
    pthread_mutex_t *fork;
    struct timeval start_time;
}   t_philo;

typedef struct s_info
{
    int num_of_philo;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int num_of_meals;
    t_philo *philo;
}   t_info;


int	ft_atoi(char *str);
#endif