/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:27 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/13 12:59:35 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void ft_take_rfork(t_data  *data, t_philo *philo)
{
    pthread_mutex_lock(&data->forks[philo->philo_id - 1]);
    philo->rfork = 1;
	pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 1){
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&data->death_mutex);
    printf("%d %d has taken a fork\n", ft_current_time(data),philo->philo_id);
}

void ft_take_lfork(t_data  *data, t_philo *philo)
{
    pthread_mutex_lock(&data->forks[philo->philo_id % data->nbr_of_philos]);
    philo->lfork = 1;
    pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 1){
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&data->death_mutex);
    printf("%d %d has taken a fork\n", ft_current_time(data),philo->philo_id);
}

void ft_eat(t_data  *data, t_philo *philo)
{
    pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 1){
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&data->death_mutex);
    printf("%d %d is eating\n", ft_current_time(data),philo->philo_id);
    philo->time_of_last_eat = ft_current_time(data);
    // usleep(data->time_to_eat * 1000);
	ft_msleep(data->time_to_eat, data);
    philo->eat_times++;
    philo->rfork = 0;
    philo->lfork = 0;
    pthread_mutex_unlock(&data->forks[philo->philo_id - 1]);
    pthread_mutex_unlock(&data->forks[philo->philo_id % data->nbr_of_philos]);
}

void ft_sleep_think(t_data  *data, t_philo *philo)
{
    pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 1){
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&data->death_mutex);
    printf("%d %d is sleeping\n", ft_current_time(data),philo->philo_id);
    // usleep(data->time_to_sleep * 1000);
	ft_msleep(data->time_to_eat, data);
    pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 1){
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&data->death_mutex);
    printf("%d %d is thinking\n", ft_current_time(data),philo->philo_id);
}

void ft_death_check(t_data  *data, t_philo *philo)
{
	int time_without_eat;
	int status_before_eat;

	time_without_eat = ft_current_time(data) - philo->time_of_last_eat;
	status_before_eat = 1;
	pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 1){
		pthread_mutex_unlock(&data->death_mutex);
		return ;
	}
	else
		pthread_mutex_unlock(&data->death_mutex);
	printf("%d =======> check death of philo %d ==> time without eat : %d\n", ft_current_time(data), philo->philo_id, time_without_eat);
	if (philo->eat_times == 0 && ft_current_time(data) >= data->time_to_die)
		status_before_eat = 0;
	if (time_without_eat >= data->time_to_die || status_before_eat == 0)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->death_status = 1;
		pthread_mutex_unlock(&data->death_mutex);
		printf("%d %d died\n", ft_current_time(data),philo->philo_id);
	}
}