/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:54:23 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/28 12:08:26 by malja-fa         ###   ########.fr       */
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
        || info->time_to_eat <= 0 || info->time_to_sleep <= 0)
            return (false);
    return (true);
}
bool    init_mutex(t_info *info)
{
    int i;

    i = 0;
    info->philo = malloc(info->num_of_philo * sizeof(t_philo));
    if (!info->philo)
        return (false);
    info->philo->fork = malloc(info->num_of_philo * sizeof(pthread_mutex_t));
    if(!info->philo->fork)
    {
        free (info->philo);
        return (false);
    }
    while (i < info->num_of_philo)
    {
        if (pthread_mutex_init(&info->philo->fork[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&info->philo->fork[i]);
            free (info->philo);
            free (info->philo->fork);
            return (false);
        }
        i++;
    }
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
    if(!handle_minus(info, argv) || !init_mutex(info))
        return (false);
    gettimeofday(&info->philo->start_time, NULL);
    return (true);
}

int main(int argc, char **argv)
{
    t_info  *info;
    int i;

    i = 0;    
    info = malloc(sizeof(t_info));
    if (!info)  
        return (1);
    if (!handle_input(argv, argc, info))
    {
        write(2, "Error: Invalid input or initialization failure\n", 47);
        free (info);
        return (1);
    }



    while (i <info->num_of_philo)
        pthread_mutex_destroy(&info->philo->fork[i++]);
    free (info->philo->fork);
    free (info->philo);
    free (info);
    return (0);
}
