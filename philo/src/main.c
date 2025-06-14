/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-boom <mohammad-boom@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:54:23 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/15 20:14:30 by mohammad-bo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_bool	handle_minus(t_info *info, char **argv)
/**
 * handle_minus - Handles the input and checks if it is valid.
 * the error occurs when the input is less than or equal to 0.
 * and the number of meals is equal 0.
 * and number of philo is less than or equal to 1.
 * cause when there is only one philo, he can't eat alone.
 *
 */
{
	info->num_of_philo = parse_atoi(argv[1]);
	info->time_to_die = parse_atoi(argv[2]);
	info->time_to_eat = parse_atoi(argv[3]);
	info->time_to_sleep = parse_atoi(argv[4]);
	info->simulation_over = false;
	if (info->num_of_philo <= 0 || info->time_to_die <= 0
		|| info->time_to_eat <= 0 || info->time_to_sleep <= 0
		|| (info->flag == true && info->num_of_meals <= 0))
		return (false);
	pthread_mutex_init(&info->death_mutex, NULL);
	pthread_mutex_init(&info->simulation_mutex, NULL);
	pthread_mutex_init(&info->monitor_mutex, NULL);
	return (true);
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
		info->flag = false;
	}
	else if (argc == 6)
	{
		info->num_of_meals = parse_atoi(argv[5]);
		info->flag = true;
	}
	else
		return (false);
	if (!handle_minus(info, argv))
		return (false);
	return (true);
}

/* t_bool	check_if_died(t_philo *philo)
{
	if (philo->state == died || (philo->meals_eaten >= philo->info->num_of_meals
			&& philo->info->num_of_meals != -1))
		return (1);
	return (0);
} */

void	monitor(t_philo **philo, t_info *info)
{
	t_philo	*thread = *philo;

	while (1)
	{
		pthread_mutex_lock(&info->death_mutex);
		if (check_philo_state(thread))
		{
			info->simulation_over = true;
			pthread_mutex_unlock(&info->death_mutex);
			break;
		}
		pthread_mutex_unlock(&info->death_mutex);
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;
	t_philo	*threads;

	threads = NULL;
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	memset(info, 0, sizeof(t_info));
	if (!handle_input(argv, argc, info))
	{
		write(2, "Error: Invalid input\n", 22);
		free(info);
		return (1);
	}
	if (creating_list(info, argv, &threads))
		return (1);
	if (creating_threads(info, &threads))
		return (1);
	monitor(&threads, info);
	join_threads(info, &threads);
	pthread_mutex_destroy(&info->death_mutex);
	pthread_mutex_destroy(&info->simulation_mutex);
	pthread_mutex_destroy(&info->printf_mutex);
	pthread_mutex_destroy(&info->monitor_mutex);
	lst_clear(&threads);
	free(info);
	return (0);
}
