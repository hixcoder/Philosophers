/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:27 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/23 22:22:41 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_rfork(t_data *data, t_philo *philo)
{
	if (!data->forks || !data->philos)
		return ;
	pthread_mutex_lock(&data->forks[philo->philo_id - 1]);
	if (!data->forks || !data->philos)
		return ;
	philo->rfork = 1;
	if (data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (!data->forks || !data->philos)
			return ;
		printf("%ld %d has taken a fork\n", \
		ft_current_time(data), philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

void	ft_take_lfork(t_data *data, t_philo *philo)
{
	if (!data->forks || !data->philos)
		return ;
	pthread_mutex_lock(&data->forks[philo->philo_id % data->nbr_of_philos]);
	if (!data->forks || !data->philos)
		return ;
	philo->lfork = 1;
	if (data->death_status == 0)
	{
		if (!data->forks || !data->philos)
			return ;
		pthread_mutex_lock(&data->print_mutex);
		if (!data->forks || !data->philos)
			return ;
		printf("%ld %d has taken a fork\n", \
		ft_current_time(data), philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

void	ft_eat(t_data *data, t_philo *philo)
{
	if (data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (!data->forks || !data->philos)
			return ;
		printf("%ld %d is eating\n", ft_current_time(data), philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
		philo->time_of_last_eat = ft_current_time(data);
		ft_msleep(data->time_to_eat, data);
		philo->eat_times++;
	}
	philo->rfork = 0;
	philo->lfork = 0;
	if (!data->forks || !data->philos)
		return ;
	pthread_mutex_unlock(&data->forks[philo->philo_id - 1]);
	if (!data->forks || !data->philos)
		return ;
	pthread_mutex_unlock(&data->forks[philo->philo_id % data->nbr_of_philos]);
}

void	ft_sleep_think(t_data *data, t_philo *philo)
{
	if (data->death_status == 0)
	{
		if (!data->forks || !data->philos)
			return ;
		pthread_mutex_lock(&data->print_mutex);
		if (!data->forks || !data->philos)
			return ;
		printf("%ld %d is sleeping\n", ft_current_time(data), philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
		ft_msleep(data->time_to_sleep, data);
	}
	if (data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (!data->forks || !data->philos)
			return ;
		printf("%ld %d is thinking\n", ft_current_time(data), philo->philo_id);
		pthread_mutex_unlock(&data->print_mutex);
	}
}
