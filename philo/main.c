/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/09 17:04:07 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>


void *routine(void *arg)
{
    t_philo *philos;
    t_data  *data;
    
    philos = (t_philo *) arg;
    data = (t_data *) philos->data;
    if(philos->philo_id % 2 == 0)
        usleep(100);
    while(1){
    ft_take_rfork(data, philos);
    ft_take_lfork(data, philos);

    ft_eat(data, philos);
    if (philos->eat_times >= data->nbr_of_meals && data->nbr_of_meals != 0)
        break ;
    ft_sleep_think(data, philos);
    
    // printf("2 - time_of_last_eat of philo %d = %d\n", philos->philo_id ,philos->time_of_last_eat);
    if (philos->time_of_last_eat >= data->time_to_die)
        ft_died(data, philos);
    }
   return (NULL);
}

int    ft_create_philos(t_data *data)
{
    int i;
    
    data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
    if (data->philos == NULL)
        ft_malloc_error(data->philos, data, 1);
    i = -1;
    while (++i < data->nbr_of_philos)
    {
        data->philos[i].philo_id = i + 1;
        data->philos[i].data = (struct t_data*)data;
        data->philos->eat_times = 0;
        data->philos->time_of_last_eat = 0;
        if (pthread_create(&data->philos[i].philo_th, NULL, &routine, (void *) &data->philos[i]) != 0)
            ft_error("pthread_create Error");
    }
    i = -1;
    while (++i < data->nbr_of_philos)
    {
        if (pthread_join(data->philos[i].philo_th, NULL) != 0)
            ft_error("pthread_join Error");
    }
    return (SUCCESS);
}

// => Please Enter: ./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals]
// => [nbr_of_meals] is optional

int main(int ac, char **av)
{
    t_data data;
    
    if (ac >= 5 && ac <= 6)
    {
        ft_parse_data(&data, av);
        ft_create_forks(&data);
        ft_create_philos(&data);
    }
    else
        ft_error("Invalid Arguments");
    return (SUCCESS);
}
