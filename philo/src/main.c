/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:54:23 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/26 13:40:23 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static t_bool	setup(int argc, char **argv, t_info **info, t_philo **philos)
{
	*philos = NULL;
	*info = malloc(sizeof(t_info));
	if (!*info)
		return (FALSE);
	memset(*info, 0, sizeof(t_info));
	if (!handle_input(argv, argc, *info))
	{
		write(2, "Error: Invalid input\n", 22);
		free(*info);
		return (FALSE);
	}
	if (!init_forks(*info) || !init_philos(*info, philos))
	{
		write(2, "Error: Failed to initialize forks or philos\n", 45);
		destroy_info(*info);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	start_simulation(t_info *info, t_philo *philos,
	pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, philos) != 0)
	{
		write(2, "Error: Failed to create monitor thread\n", 40);
		return (FALSE);
	}
	join_threads(info, &philos);
	return (TRUE);
}

static void	cleanup(t_info *info, t_philo *philos, t_bool join_monitor)
{
	if (!join_monitor)
		join_threads(info, &philos);
	destroy_info(info);
}

int	main(int argc, char **argv)
{
	t_info		*info;
	t_philo		*philos;
	pthread_t	monitor;

	if (!setup(argc, argv, &info, &philos))
		return (1);
	if (!start_simulation(info, philos, &monitor))
	{
		cleanup(info, philos, FALSE);
		return (1);
	}
	pthread_join(monitor, NULL);
	cleanup(info, philos, TRUE);
	return (0);
}
