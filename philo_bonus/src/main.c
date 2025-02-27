/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 08:50:44 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/13 09:17:07 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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
		|| info->num_of_meals == 0)
		return (false);
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
		info->num_of_meals = -1;
	else if (argc == 6)
		info->num_of_meals = parse_atoi(argv[5]);
	else
		return (false);
	if (!handle_minus(info, argv))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_info	*info;

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
}