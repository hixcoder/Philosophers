/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:27 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/12 11:55:51 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void ft_take_rfork(t_data  *data, t_philo *philo)
{
    if (data->isforks_used[philo->philo_id - 1] == 0)
    {
        pthread_mutex_lock(&data->forks[philo->philo_id - 1]);
        philo->rfork = 1;
        data->isforks_used[philo->philo_id - 1] = 1;
        // printf("=======> fork %d is used by philo %d\n",philo->philo_id - 1, philo->philo_id);
        printf("%d %d has taken a fork\n", ft_current_time(data),philo->philo_id);
    }
    else
        philo->rfork = 0;
}

void ft_take_lfork(t_data  *data, t_philo *philo)
{
    if (data->isforks_used[philo->philo_id % data->nbr_of_philos] == 0)
    {
        pthread_mutex_lock(&data->forks[philo->philo_id % data->nbr_of_philos]);
        philo->lfork = 1;
        data->isforks_used[philo->philo_id % data->nbr_of_philos] = 1;
        // printf("=======> fork %d is used by philo %d\n",philo->philo_id % data->nbr_of_philos, philo->philo_id);
        printf("%d %d has taken a fork\n", ft_current_time(data),philo->philo_id);
    }
    else
        philo->lfork = 0;
}

void ft_eat(t_data  *data, t_philo *philo)
{
    printf("%d %d is eating\n", ft_current_time(data),philo->philo_id);
    philo->time_of_last_eat = ft_current_time(data);
    usleep(data->time_to_eat * 1000);
    philo->eat_times++;
    data->isforks_used[philo->philo_id - 1] = 0;
    data->isforks_used[philo->philo_id % data->nbr_of_philos] = 0;
    pthread_mutex_unlock(&data->forks[philo->philo_id - 1]);
    pthread_mutex_unlock(&data->forks[philo->philo_id % data->nbr_of_philos]);
}

void ft_sleep_think(t_data  *data, t_philo *philo)
{
    printf("%d %d is sleeping\n", ft_current_time(data),philo->philo_id);
    usleep(data->time_to_sleep * 1000);
    printf("%d %d is thinking\n", ft_current_time(data),philo->philo_id);
}

int ft_death_check(t_data  *data, t_philo *philo)
{
	int time_without_eat;
	int status_before_eat;

	time_without_eat = ft_current_time(data) - philo->time_of_last_eat;
	status_before_eat = 1;
	// printf("%d =======> check death of philo %d ==> time without eat : %d\n", ft_current_time(data), philo->philo_id, time_without_eat);
	// pthread_mutex_lock(&data->death_mutex);
	if (data->death_status == 1)
		return (1);
	// pthread_mutex_unlock(&data->death_mutex);
	if (philo->eat_times == 0 && ft_current_time(data) >= data->time_to_die)
		status_before_eat = 0;
	if (time_without_eat >= data->time_to_die || status_before_eat == 0)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->death_status = 1;
		pthread_mutex_unlock(&data->death_mutex);
		printf("%d %d died\n", ft_current_time(data),philo->philo_id);
		return(1);
	}
	return (0);
}