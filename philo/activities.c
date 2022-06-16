/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:27 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/15 13:27:50 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void ft_take_rfork(t_data  *data, t_philo *philo)
{
    pthread_mutex_lock(&data->forks[philo->philo_id - 1]);
    philo->rfork = 1;
	if (data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
   		printf("%d %d has taken a fork\n", ft_current_time(data),philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

void ft_take_lfork(t_data  *data, t_philo *philo)
{
	if (data->nbr_of_philos > 1)
	{
		pthread_mutex_lock(&data->forks[philo->philo_id % data->nbr_of_philos]);
		philo->lfork = 1;
		if (data->death_status == 0)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%d %d has taken a fork\n", ft_current_time(data),philo->philo_id);
			pthread_mutex_unlock(&data->print_mutex);
		}
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->philo_id - 1]);
		ft_msleep(data->time_to_die, data);
	}
	
}

void ft_eat(t_data  *data, t_philo *philo)
{
    if (data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%d %d is eating\n", ft_current_time(data),philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
		philo->time_of_last_eat = ft_current_time(data);
		ft_msleep(data->time_to_eat, data);
		philo->eat_times++;
	}
    philo->rfork = 0;
    philo->lfork = 0;
    pthread_mutex_unlock(&data->forks[philo->philo_id - 1]);
    pthread_mutex_unlock(&data->forks[philo->philo_id % data->nbr_of_philos]);
}

void ft_sleep_think(t_data  *data, t_philo *philo)
{
    if (data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
    	printf("%d %d is sleeping\n", ft_current_time(data),philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
		ft_msleep(data->time_to_eat, data);
	}
    if (data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
    	printf("%d %d is thinking\n", ft_current_time(data),philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

void ft_death_check(t_data  *data, t_philo *philo)
{
	int time_without_eat;

	time_without_eat = ft_current_time(data) - philo->time_of_last_eat;
	if (time_without_eat >= data->time_to_die && data->death_status == 0)
	{
		printf("%d =======> check death of philo %d ==> time without eat : %d\n", ft_current_time(data), philo->philo_id, time_without_eat);
		pthread_mutex_lock(&data->death_mutex);
		data->death_status = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%d %d died\n", ft_current_time(data),philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
	}
}