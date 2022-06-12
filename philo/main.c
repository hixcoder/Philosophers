/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/12 11:49:57 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>


void *routine(void *arg)
{
    t_philo *philo;
    t_data  *data;
    
    philo = (t_philo *) arg;
    data = (t_data *) philo->data;
    if(philo->philo_id % 2 == 0)
        usleep(1000);
    while(1)
    {
        ft_take_rfork(data, philo);
        ft_take_lfork(data, philo);
        if (philo->lfork == 1 && philo->rfork == 1)
        {
            ft_eat(data, philo);
            if (ft_death_check(data, philo) == 1)
                break;
            if (philo->eat_times >= data->nbr_of_meals && data->nbr_of_meals != 0)
                break ;
            ft_sleep_think(data, philo);
            if (ft_death_check(data, philo) == 1)
                break;
        }
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

// => Please Enter: ./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals]
// => [nbr_of_meals] is optional

int main(int ac, char **av)
{
    t_data  data;
    int     status;
    
    if (ac >= 5 && ac <= 6)
    {
        ft_parse_data(&data, av);
        ft_create_forks(&data);
        status = ft_create_philos(&data);
        ft_clean(&data);
    }
    else
        status = ft_error("Invalid Arguments");
    return (status);
}
