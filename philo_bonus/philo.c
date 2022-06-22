/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:43:39 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/22 13:09:23 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_forks(t_data *data)
{
	int	i;

	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	data->forks_sem = sem_open("forks_sem", O_CREAT, 0644, data->nbr_of_philos);
	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	if (data->forks_sem == SEM_FAILED || data->print_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
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
			if (philo->eat_times >= data->nbr_of_meals
				&& data->nbr_of_meals > 0)
				break ;
			ft_sleep_think(data, philo);
		}
	}
	return (NULL);
}

void	ft_create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (data->philos == NULL)
		ft_malloc_error(data->philos);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].data = (struct t_data *) data;
		data->philos[i].eat_times = 0;
		data->philos[i].time_of_last_eat = 0;
		data->philos[i].lfork = 0;
		data->philos[i].rfork = 0;
		if (fork() == 0){
			routine(&data->philos[i]);
		}
	}
	ft_death_checker(data);
}
