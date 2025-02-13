/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:52:03 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/11 09:01:04 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	creating_list(t_info *info, char **argv, t_philo **threads)
/**
 * creating_list - Creates a circular doubly linked list of threads.
 * @info: The info struct that contains the data to be passed to the threads.
 * @argv: The arguments passed to the program.
 * @threads: A pointer to the head of the list.
 * @return: 1 if an error occurs, 0 otherwise.
 */
{
	int		i;
	t_philo	*thread;

	i = 0;
	thread = NULL;
	while (i < info->num_of_philo)
	{
		thread = new_node(thinking, i + 1, argv, info);
		if (!thread)
		{
			lst_clear(threads);
			free(info);
			return (1);
		}
		add_back(threads, thread);
		if (!init_mutex(&thread->fork, info))
		{
			lst_clear(threads);
			free(info);
			return (1);
		}
		i++;
	}
	return (0);
}

int	creating_threads(t_info *info, t_philo **threads)
/**
 * creating_threads - Creates the threads.
 * @info: The info struct that contains the data to be passed to the threads.
 * @threads: A pointer to the head of the list.
 * @return: 1 if an error occurs, 0 otherwise.
 */
{
	int		i;
	t_philo	*thread;

	i = 0;
	thread = *threads;
	while (i < info->num_of_philo)
	{
		if (pthread_create(&thread->philo, NULL, routine, thread) != 0)
		{
			write(2, "Error: Failed to create thread\n", 31);
			while (--i >= 0)
			{
				thread = thread->prev;
				pthread_join(thread->philo, NULL);
			}
			lst_clear(threads);
			free(info);
			return (1);
		}
		thread = thread->next;
		i++;
	}
	return (0);
}

void	join_threads(t_info *info, t_philo **thread)
/**
 * join_threads - Joins the threads.
 * @info: The info struct that contains the data to be passed to the threads.
 * @thread: A pointer to the head of the list.
 * @return: 1 if an error occurs, 0 otherwise.
 */
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join((*thread)->philo, NULL);
		*thread = (*thread)->next;
		i++;
	}
}
