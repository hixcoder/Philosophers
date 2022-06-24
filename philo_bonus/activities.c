/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:12:27 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/24 10:42:30 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_rfork(t_data *data, t_philo *philo)
{
	sem_wait(data->forks_sem);
	philo->rfork = 1;
	sem_wait(data->print_sem);
	printf("%ld %d has taken a fork\n", ft_current_time(data), philo->philo_id);
	sem_post(data->print_sem);
}

void	ft_take_lfork(t_data *data, t_philo *philo)
{
	sem_wait(data->forks_sem);
	philo->lfork = 1;
	sem_wait(data->print_sem);
	printf("%ld %d has taken a fork\n", ft_current_time(data), philo->philo_id);
	sem_post(data->print_sem);
}

void	ft_eat(t_data *data, t_philo *philo)
{
	sem_wait(data->print_sem);
	printf("%ld %d is eating\n", ft_current_time(data), philo->philo_id);
	sem_post(data->print_sem);
	philo->time_of_last_eat = ft_current_time(data);
	ft_msleep(data->time_to_eat, data);
	philo->eat_times++;
	philo->rfork = 0;
	philo->lfork = 0;
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
}

void	ft_sleep_think(t_data *data, t_philo *philo)
{
	sem_wait(data->print_sem);
	printf("%ld %d is sleeping\n", ft_current_time(data), philo->philo_id);
	sem_post(data->print_sem);
	ft_msleep(data->time_to_sleep, data);
	sem_wait(data->print_sem);
	printf("%ld %d is thinking\n", ft_current_time(data), philo->philo_id);
	sem_post(data->print_sem);
}
