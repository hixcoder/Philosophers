/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/05/31 13:24:42 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

void *routine()
{
   
   return (NULL);
}

pthread_t *ft_make_threads(t_data *data)
{
    pthread_t *th;
    int i;

    th = malloc(sizeof(pthread_t) * data->nbr_of_philos);
    if (!th)
        ft_error("Allocation Error");
    i = -1;
    while (i++ < data->nbr_of_philos)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
            ft_error("pthread_create Error");
    }
    i = -1;
    while (i++ < data->nbr_of_philos)
    {
        if (pthread_join(&th[i], NULL) != 0)
            ft_error("pthread_join Error");
    }
}

// => Please Enter: ./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals]
// => [nbr_of_meals] is optional

int main(int ac, char **av)
{
    t_data data;
    struct timeval current_time;
    // pthread_t *th;
    
    if (ac >= 5 && ac <= 6)
    {
        ft_parse_args(&data, av);
        gettimeofday(&current_time, NULL);
        printf("seconds : %d\nmicro seconds : %d",(int)current_time.tv_sec, (int)current_time.tv_usec);
    }
    else
        ft_error("Invalid Arguments");
    return (0);
}
