/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:55:28 by malja-fa          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:17 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef enum e_state
{
	NORM,
	EATING,
	THINKING,
	SLEEPING,
	DIED
}					t_state;

typedef struct s_info
{
	int				num_of_philo;
	long			time_to_eat;
	long			time_to_sleep;
	_Atomic long	time_to_die;
	_Atomic int		num_of_meals;
	_Atomic int		simulation_over;
	int				flag;
	long			start_time;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*fork;
}					t_info;

typedef struct s_philo
{
	_Atomic int		state;
	_Atomic long	last_meal;
	_Atomic int		meals_eaten;
	pthread_t		philo;
	t_info			*info;
	int				id;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}					t_philo;

long long			parse_atoi(char *str);
void				*routine(void *arg);
void				safe_printf(const char *msg, pthread_mutex_t *printf_mutex,
						long current_time, t_philo *philo);
long				get_time_in_ms(void);
t_bool				check_death(t_philo *philo);
t_bool				check_philo_state(t_philo *philo);
void				change_statement(t_philo *philo);
t_bool				thinking_thread(t_philo *philo, long simulation_time);
t_bool				sleeping_thread(t_philo *philo, long simulation_time);
t_bool				eating_thread(t_philo *philo, long simulation_time);
t_bool				acquire_forks(t_philo *philo, long simulation_time);

void				release_forks(t_philo *philo);
void				join_threads(t_info *info, t_philo **thread);
int					ft_usleep(long long time_in_ms, t_philo *philo);
t_bool				check_one_philo(t_philo *philo, long time);
t_bool				init_philos(t_info *info, t_philo **philos);
t_bool				init_forks(t_info *info);
void				*monitor_routine(void *philos);
void				destroy_info(t_info *info);
t_bool				handle_minus(t_info *info, char **argv);
t_bool				handle_input(char **argv, int argc, t_info *info);
#endif