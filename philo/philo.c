/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:43:39 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/23 23:12:59 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_forks(t_data *data)
{
	int	i;

	data->forks = malloc(data->nbr_of_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ft_malloc_error(data->forks, data, 0));
	pthread_mutex_init(&data->print_mutex, NULL);
	i = -1;
	while (++i < data->nbr_of_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return (SUCCESS);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) arg;
	data = (t_data *) philo->data;
	if (philo->philo_id % 2 == 0)
		usleep(500);
	while (data->death_status == 0)
	{
		ft_take_rfork(data, philo);
		ft_take_lfork(data, philo);
		if (philo->lfork == 1 && philo->rfork == 1 && data->nbr_of_meals != 0)
		{
			ft_eat(data, philo);
			if (philo->eat_times == data->nbr_of_meals)
			{
				data->philos_finished_eating++;
				break ;
			}
			ft_sleep_think(data, philo);
		}
	}
	return (NULL);
}

int	ft_create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (data->philos == NULL)
		return (ft_error("Allocation Error"));
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].data = (struct t_data *) data;
		data->philos[i].eat_times = 0;
		data->philos[i].time_of_last_eat = 0;
		data->philos[i].lfork = 0;
		data->philos[i].rfork = 0;
		if (pthread_create(&data->philos[i].philo_th, NULL, \
		&routine, (void *) &data->philos[i]) != 0)
			return (ft_error("Thread Error"));
		if (pthread_detach(data->philos[i].philo_th) != 0)
			return (ft_error("Thread Error"));
	}
	ft_death_checker(data);
	return (SUCCESS);
}
