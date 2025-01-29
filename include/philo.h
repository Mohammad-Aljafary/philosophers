/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:55:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/29 13:58:28 by malja-fa         ###   ########.fr       */
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

typedef enum    e_bool
{
    false,
    true    
}   bool;

typedef enum    e_state
{
    eating,
    thinking,
    sleeping,
    died
}   state;

typedef enum    e_fork
{
    not_occupied,
    occupied
}   forks;

typedef struct s_info
{
    int num_of_philo;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int num_of_meals;

}   t_info;

typedef struct s_philo
{
    pthread_t   philo;
    int state;
    int id;
    struct s_philo *next;
    struct s_philo *prev;
    char    **argv;
}   t_philo;

typedef struct s_fork
{
    pthread_mutex_t *fork;
    int *fork_status;
}   t_fork;



t_philo *new_node(int status, int id, char **argv);
void    add_back(t_philo **lst, t_philo *node);
void lst_clear(t_philo **lst);
int	ft_atoi(char *str);
void	*routine(void *arg);
#endif