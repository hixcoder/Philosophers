/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:28:06 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/23 15:07:43 by hboumahd         ###   ########.fr       */
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

void	ft_msleep(int sleep_ms, t_data *data)
{
	long	end_time;

	end_time = ft_current_time(data) + sleep_ms;
	while (ft_current_time(data) < end_time)
		usleep(1);
}

void	ft_is_died(t_philo	*philo)
{
	int	time_without_eat;
	t_data *data;
	
	data = (t_data *) philo->data;
	while(1)
	{
		time_without_eat = ft_current_time(data) - philo->time_of_last_eat;
		if (time_without_eat >= data->time_to_die)
		{
			sem_wait(data->print_sem);
			printf("%ld %d died\n", ft_current_time(data), philo->philo_id);
			sem_post(data->done_sem);
			exit(0);
		}
	}
} 

void	*eated_philos(void *arg)
{
	int		i;
	t_data	*data;
	
	i = -1;
	data = (t_data *) arg;
	while(++i < data->nbr_of_philos)
		sem_wait(data->finish_eat_sem);
	while(++i < data->nbr_of_philos)
		kill(data->pids[i], SIGKILL);
	waitpid(-1, NULL, 0);
	exit(0);
}

void	ft_wait(t_data *data)
{
	int i;
	pthread_t th;

	i = -1;
	if (data->nbr_of_meals > 0)
	{
		if (pthread_create(&th, NULL, &eated_philos, (void *) data) != 0)
			ft_malloc_error(data, "Thread Error");
		if (pthread_detach(th) != 0)
			ft_malloc_error(data, "Thread Error");
	}
	sem_wait(data->done_sem);
	while(++i < data->nbr_of_philos)
		kill(data->pids[i], SIGKILL);
	waitpid(-1, NULL, 0);
}
