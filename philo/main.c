/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/04 13:16:03 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>


void *routine(void *arg)
{
    t_data *data;
    
    data = (t_data *) arg;
    printf("%d %d has taken a fork\n", ft_time(),data->philos->philo_id);
    printf("%d %d is eating\n", ft_time(),data->philos->philo_id);
    printf("%d %d is sleeping\n", ft_time(),data->philos->philo_id);
    printf("%d %d is thinking\n", ft_time(),data->philos->philo_id);
    printf("%d %d died\n", ft_time(),data->philos->philo_id);
   
   return (NULL);
}

void    ft_create_philos(t_data *data)
{
    int i;
    
    data->philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
    if (data->philos == NULL)
        ft_malloc_error(data->philos);
    i = -1;
    while (i++ < data->nbr_of_philos)
    {
        data->philos->philo_id = i;
        if (pthread_create(&data->philos[i].philo_th, NULL, &routine, (void *) data) != 0)
            ft_error("pthread_create Error");
    }
    i = -1;
    while (i++ < data->nbr_of_philos)
    {
        if (pthread_join(data->philos[i].philo_th, NULL) != 0)
            ft_error("pthread_join Error");
    }
}


// => Please Enter: ./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals]
// => [nbr_of_meals] is optional

int main(int ac, char **av)
{
    t_data data;
    
    // pthread_t *th;
    
    if (ac >= 5 && ac <= 6)
    {
        ft_parse_data(&data, av);
        ft_create_forks(&data);
        ft_create_philos(&data);
    }
    else
        ft_error("Invalid Arguments");
    return (0);
}
