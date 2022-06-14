/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:43:39 by ubunto            #+#    #+#             */
/*   Updated: 2022/06/14 17:39:19 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_create_forks(t_data *data)
{
    int i;
    
    data->forks = malloc(data->nbr_of_philos * sizeof(pthread_mutex_t));
    if (!data->forks)
        return (ft_malloc_error(data->forks, data, 0));
    pthread_mutex_init(&data->death_mutex, NULL);
    pthread_mutex_init(&data->print_mutex, NULL);
    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_init(&data->forks[i], NULL);
    return (SUCCESS);
}


void *routine(void *arg)
{
    t_philo *philo;
    t_data  *data;
    
    philo = (t_philo *) arg;
    data = (t_data *) philo->data;
    if(philo->philo_id % 2 == 0)
        usleep(100);
    while(data->death_status == 0)
    {
        ft_take_rfork(data, philo);
        ft_take_lfork(data, philo);
        if (philo->lfork == 1 && philo->rfork == 1)
        {
            ft_eat(data, philo);
            if (philo->eat_times >= data->nbr_of_meals && data->nbr_of_meals > 0)
                break ;
            ft_sleep_think(data, philo);
        }
        ft_death_check(data, philo);
    }
   return (NULL);
}

int    ft_create_philos(t_data *data)
{
    int i;
    
    data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
    if (data->philos == NULL)
        return (ERROR);
    i = -1;
    while (++i < data->nbr_of_philos)
    {
        data->philos[i].philo_id = i + 1;
        data->philos[i].data = (struct t_data*)data;
        data->philos[i].eat_times = 0;
        data->philos[i].time_of_last_eat = 0;
        data->philos[i].lfork = 0;
        data->philos[i].rfork = 0;
        if (pthread_create(&data->philos[i].philo_th, NULL, &routine, (void *) &data->philos[i]) != 0)
            return (ERROR);
    }
    i = -1;
    while (++i < data->nbr_of_philos)
    {
        if (pthread_join(data->philos[i].philo_th, NULL) != 0)
            return (ERROR);
    }
    return (SUCCESS);
}