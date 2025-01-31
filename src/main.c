/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:54:23 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/31 21:37:51 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool    handle_minus(t_info *info, char **argv)
{
    info->num_of_philo = parse_atoi(argv[1]);
    info->time_to_die = parse_atoi(argv[2]);
    info->time_to_eat = parse_atoi(argv[3]);
    info->time_to_sleep = parse_atoi(argv[4]);
    if (info->num_of_philo <= 0 || info->time_to_die <= 0 
        || info->time_to_eat <= 0 || info->time_to_sleep <= 0
        || info->num_of_meals == 0)
            return (false);
    return (true);
}

bool    handle_input(char **argv, int argc, t_info *info)
{
    info->num_of_meals = -1;
    if (argc == 5)
        info->num_of_meals = -1;
    else if (argc == 6)
        info->num_of_meals = parse_atoi(argv[5]);
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
    int i;

    i = 0;
    threads = NULL;
    info = malloc(sizeof(t_info));
    if (info)
        memset(info, 0, sizeof(t_info));
    if (!info)  
        return (1);
    if (!handle_input(argv, argc, info))
    {
        write(2, "Error: Invalid input\n", 22);
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
    monitor.philo = threads;
    if (pthread_create(&monitor.monitor, NULL, monitor_check, &monitor) != 0)
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

