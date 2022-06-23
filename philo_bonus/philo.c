/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:43:39 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/23 23:31:30 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_forks(t_data *data)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("done_sem");
	sem_unlink("finish_eat_sem");
	data->forks_sem = sem_open("forks_sem", O_CREAT, 0644, data->nbr_of_philos);
	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	data->done_sem = sem_open("done_sem", O_CREAT, 0644, 0);
	data->finish_eat_sem = sem_open("finish_eat_sem", O_CREAT, 0644, 0);
	if (data->forks_sem == SEM_FAILED || data->print_sem == SEM_FAILED || data->done_sem == SEM_FAILED  || data->finish_eat_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) arg;
	data = (t_data *) philo->data;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (1)
	{
		ft_take_rfork(data, philo);
		ft_take_lfork(data, philo);
		if (philo->lfork == 1 && philo->rfork == 1 && data->nbr_of_meals != 0)
		{
			ft_eat(data, philo);
			if (philo->eat_times == data->nbr_of_meals && data->nbr_of_meals > 0)
			{
				sem_post(data->finish_eat_sem);
				exit(EXIT_SUCCESS);
			}
			ft_sleep_think(data, philo);
		}
	}
	return (NULL);
}

void	ft_philo_init(t_data *data, int i)
{
	data->philos[i].philo_id = i + 1;
	data->philos[i].data = (struct t_data *) data;
	data->philos[i].eat_times = 0;
	data->philos[i].time_of_last_eat = 0;
	data->philos[i].lfork = 0;
	data->philos[i].rfork = 0;
}

void	ft_create_philos(t_data *data)
{
	int	i;
	int j;

	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	data->pids = malloc(sizeof(int) * data->nbr_of_philos);
	if (data->philos == NULL || data->pids == NULL)
		ft_malloc_error(data, "Allocation Error");
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		ft_philo_init(data, i);
		j = fork();
		if (j > 0)
			data->pids[i] = j;
		if (j == 0)
		{
			if (pthread_create(&data->philos[i].philo_th, NULL, &routine, (void *) &data->philos[i]) != 0)
				ft_malloc_error(data, "Thread Error");
			if (pthread_detach(data->philos[i].philo_th) != 0)
				ft_malloc_error(data, "Thread Error");
			ft_is_died(&data->philos[i]);
		}
		else if (j == -1)
			ft_malloc_error(data, "Fork Error");
		
	}
}

