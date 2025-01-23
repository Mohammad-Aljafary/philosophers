/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:54:23 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/23 22:53:59 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *handle_minus(t_info *info)
{
    if (info->num_of_philo <= 0 || info->time_to_die <= 0 
        || info->time_to_eat <= 0 || info->time_to_sleep <= 0)
            return (NULL);
    return ((void *)1);
}

void    *handle_input(char **argv, int argc, t_info *info)
{
    if (argc == 5)
        info->num_of_meals = -1;
    else if (argc == 6)
        info->num_of_meals = ft_atoi(argv[5]);
    else
        return (NULL);
    info->num_of_philo = ft_atoi(argv[1]);
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]);
    info->time_to_sleep = ft_atoi(argv[4]);
    if(!handle_minus(info))
        return (NULL);
    return ((void *) 1);
}

int main(int argc, char **argv)
{
    t_info  *info;
    
    info = malloc(sizeof(t_info));
    if (!info)  
        return (1);
    if (!handle_input(argv, argc, info))
        return (1);
    return (0);
}