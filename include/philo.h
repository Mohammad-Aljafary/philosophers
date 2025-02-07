/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:55:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/07 12:03:17 by malja-fa         ###   ########.fr       */
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

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"

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

typedef struct s_info
{
    int num_of_philo;
    long time_to_eat;
    long time_to_sleep;
    long time_to_die;
    int num_of_meals;
    int simulation_over;
    pthread_mutex_t printf_mutex;
    pthread_mutex_t death_mutex;
}   t_info;

typedef struct s_fork
{
    pthread_mutex_t fork;
}   t_fork;

typedef struct s_philo
{
    pthread_t   philo;
    int state;
    int id;
    struct s_philo *next;
    struct s_philo *prev;
    char    **argv;
    t_fork *fork;
    t_info  *info;
    long    last_meal;
    int             meals_eaten;
    pthread_mutex_t  lock;
}   t_philo;


t_philo *new_node(int status, int id, char **argv, t_info *info);
void    add_back(t_philo **lst, t_philo *node);
void lst_clear(t_philo **lst);
long long	parse_atoi(char *str);
void	*routine(void *arg);
void    *monitor_check(void *arg);
bool    init_mutex(t_fork **fork, t_info *info);
void    safe_printf(const char *msg, pthread_mutex_t *printf_mutex, long current_time, int id);
bool eating_thread(t_philo *philo, long simulation_time);
bool    thinking_thread(t_philo *philo, long simulation_time);
long	get_time_in_ms(void);
bool    sleeping_thread(t_philo *philo, long simulation_time);
bool    check_death(t_philo *philo);
bool    check_if_died(t_philo *philo);
void change_statement(t_philo *philo);
#endif