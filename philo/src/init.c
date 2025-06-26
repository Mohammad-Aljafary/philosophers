/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:17 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:56 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	create_thread(t_info *info, t_philo **philos)
/**
 * @info: to know the number of philos
 * @philos: to create the threads to start the routine
 * @return: false at failure in creating the threads 
 * 			true at success of creating the threads
 */
{
	int	i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_create(&(*philos)[i].philo, NULL, routine, &(*philos)[i]))
		{
			while (--i >= 0)
				pthread_join((*philos)[i].philo, NULL);
			free(*philos);
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool	init_philos(t_info *info, t_philo **philos)
/**
 * @info: to get the forks from the struct 
 * @philos: to initialize the struct with the data
 * @return: false in failure of malloc or creating threads
 * 			true at success
 */
{
	int	i;

	*philos = malloc(sizeof(t_philo) * info->num_of_philo);
	if (!*philos)
		return (FALSE);
	i = -1;
	while (++i < info->num_of_philo)
	{
		(*philos)[i].state = NORM;
		(*philos)[i].id = i + 1;
		(*philos)[i].info = info;
		(*philos)[i].last_meal = get_time_in_ms();
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].lfork = &info->fork[i];
		if (i == info->num_of_philo - 1)
			(*philos)[i].rfork = &info->fork[0];
		else
			(*philos)[i].rfork = &info->fork[i + 1];
	}
	if (!create_thread(info, philos))
		return (FALSE);
	return (TRUE);
}

t_bool	init_forks(t_info *info)
/**
 * @info: the struct that has the information needed for 
 * 			initializing the forks
 * this func init the forks 
 * @return: false at failure
 * 			true at success
 */
{
	int	i;

	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->fork)
		return (FALSE);
	i = -1;
	while (++i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&info->fork[i]);
			free(info->fork);
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool	handle_minus(t_info *info, char **argv)
/**
 * handle_minus - Handles the input and checks if it is valid.
 * the error occurs when the input is less than or equal to 0.
 * and the number of meals is equal 0.
 * and number of philo is less than or equal to 1.
 * cause when there is only one philo, he can't eat alone.
 */
{
	info->num_of_philo = parse_atoi(argv[1]);
	info->time_to_die = parse_atoi(argv[2]);
	info->time_to_eat = parse_atoi(argv[3]);
	info->time_to_sleep = parse_atoi(argv[4]);
	info->simulation_over = FALSE;
	info->start_time = get_time_in_ms();
	if (info->num_of_philo <= 0 || info->time_to_die <= 0
		|| info->time_to_eat <= 0 || info->time_to_sleep <= 0
		|| (info->flag == TRUE && info->num_of_meals <= 0))
		return (FALSE);
	if (pthread_mutex_init(&info->death_mutex, NULL))
		return (FALSE);
	if (pthread_mutex_init(&info->printf_mutex, NULL))
	{
		pthread_mutex_destroy(&info->death_mutex);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	handle_input(char **argv, int argc, t_info *info)
/**
 * handle_input - Handles the input and checks if it is valid.
 * @argv: The arguments passed to the program.
 * @argc: The number of arguments passed to the program.
 * @info: The info struct that contains the mutex and data to be passed to the thread.
 *
 */
{
	info->num_of_meals = -1;
	if (argc == 5)
	{
		info->num_of_meals = -1;
		info->flag = FALSE;
	}
	else if (argc == 6)
	{
		info->num_of_meals = parse_atoi(argv[5]);
		info->flag = TRUE;
	}
	else
		return (FALSE);
	if (!handle_minus(info, argv))
		return (FALSE);
	return (TRUE);
}
