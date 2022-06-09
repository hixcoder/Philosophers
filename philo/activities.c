/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:27 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/09 17:04:03 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void ft_take_rfork(t_data  *data, t_philo *philos)
{
    pthread_mutex_lock(&data->forks[philos->philo_id - 1]);
    printf("%d %d has taken a fork\n", ft_current_time(data),philos->philo_id);
}

void ft_take_lfork(t_data  *data, t_philo *philos)
{
    pthread_mutex_lock(&data->forks[philos->philo_id % data->nbr_of_philos]);
    printf("%d %d has taken a fork\n", ft_current_time(data),philos->philo_id);
}

void ft_eat(t_data  *data, t_philo *philos)
{
    printf("%d %d is eating\n", ft_current_time(data),philos->philo_id);
    philos->time_of_last_eat = ft_current_time(data);
    // printf("1- time_of_last_eat of philo %d = %d\n", philos->philo_id ,philos->time_of_last_eat);
    usleep(data->time_to_eat * 1000);
    philos->eat_times++;
    pthread_mutex_unlock(&data->forks[philos->philo_id - 1]);
    pthread_mutex_unlock(&data->forks[philos->philo_id % data->nbr_of_philos]);
}

void ft_sleep_think(t_data  *data, t_philo *philos)
{
    printf("%d %d is sleeping\n", ft_current_time(data),philos->philo_id);
    usleep(data->time_to_sleep * 1000);
    printf("%d %d is thinking\n", ft_current_time(data),philos->philo_id);
    philos->time_of_last_eat = ft_current_time(data) - philos->time_of_last_eat;
}

void ft_died(t_data  *data, t_philo *philos)
{
    printf("%d %d died\n", ft_current_time(data),philos->philo_id);
    free(data->forks);
    data->forks = NULL;
    free(data->philos);
    data->philos = NULL;
    exit(0);
}