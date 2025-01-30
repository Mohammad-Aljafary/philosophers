/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:54:23 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:57 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    handle_minus(t_info *info, char **argv)
{
    info->num_of_philo = ft_atoi(argv[1]);
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]);
    info->time_to_sleep = ft_atoi(argv[4]);
    if (info->num_of_philo <= 0 || info->time_to_die <= 0 
        || info->time_to_eat <= 0 || info->time_to_sleep <= 0
        || info->num_of_meals == 0)
            return (false);
    return (true);
}

bool    handle_input(char **argv, int argc, t_info *info)
{
    if (argc == 5)
        info->num_of_meals = -1;
    else if (argc == 6)
        info->num_of_meals = ft_atoi(argv[5]);
    else
        return (false);
    if(!handle_minus(info, argv))
        return (false);
    return (true);
}

int main(int argc, char **argv)
{
    t_info  *info;
    t_philo *thread;
    t_philo *threads;
    t_monitor   monitor;
    t_fork  *fork;
    int i;

    i = 0;
    threads = NULL;
    monitor.argv = argv;    
    info = malloc(sizeof(t_info));
    if (!info)  
        return (1);
    if (!handle_input(argv, argc, info))
    {
        write(2, "Error: Invalid input\n", 22);
        free(info);
        return (1);
    }
    while (i < info->num_of_philo)
    {
        thread = new_node(thinking, i, argv);
        if (!thread)
        {
            lst_clear(&threads);
            free(info);
            return (1);
        }
        add_back(&threads, thread);
        if (!init_mutex(&thread->fork))
        {
            lst_clear(&threads);
            free(info);
            return (1);
        }
        i++;
    }
    fork = malloc(sizeof(t_fork));
    if (!fork)
    {
        lst_clear(&threads);
        free(info);
        return (1);
    }
    thread = threads;
    i = 0;
    while (i < info->num_of_philo)
    {
        if (pthread_create(&thread->philo, NULL, routine, thread) != 0)
        {
            write(2, "Error: Failed to create thread\n", 31);
            lst_clear(&threads);
            free(info);
            return (1);
        }
        thread = thread->next;
        i++;
    }
    if (pthread_create(&monitor.monitor, NULL, monitor_check, threads) != 0)
    {
        write(2, "Error: Failed to create thread\n", 31);
        lst_clear(&threads);
        free(info);
        return (1);
    }
    lst_clear(&threads);
    pthread_join(monitor.monitor, NULL);
    free(info);
    return (0);
}

