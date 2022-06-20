/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:28:06 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/20 14:16:58 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ct: is the current time
long	ft_current_time(t_data *data)
{
	long			time_mill;
	struct timeval	ct;

	gettimeofday(&ct, NULL);
	if (data->start_time == 0)
		data->start_time = (1000 * ct.tv_sec + ct.tv_usec / 1000);
	time_mill = (long)(1000 * ct.tv_sec + ct.tv_usec / 1000 - data->start_time);
	return (time_mill);
}

int	ft_check_before_eat(t_data *data, t_philo *philo)
{
	while (philo->eat_times == 0)
	{
		if (ft_current_time(data) >= data->time_to_die)
			return (0);
	}
	return (1);
}

void	ft_msleep(int sleep_ms, t_data *data)
{
	long	end_time;

	end_time = ft_current_time(data) + sleep_ms;
	while (ft_current_time(data) < end_time && data->death_status == 0)
		usleep(50);
}

int	ft_is_died(t_data *data, t_philo *philo)
{
	int	time_without_eat;

	time_without_eat = ft_current_time(data) - philo->time_of_last_eat;
	if (time_without_eat >= data->time_to_die && data->death_status == 0)
	{
		pthread_mutex_lock(&data->print_mutex);
		data->death_status = 1;
		printf("%ld %d died\n", ft_current_time(data), philo->philo_id);
		return (1);
	}
	return (0);
}

void	ft_death_checker(t_data *data)
{
	int	j;

	while (1)
	{
		j = -1;
		while (++j < data->nbr_of_philos)
		{
			if (ft_is_died(data, &data->philos[j]) == 1)
				return ;
		}
	}
}
