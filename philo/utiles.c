/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:28:06 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/09 13:01:28 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ct: is the current time
int ft_time(t_data *data)
{
    int     timeMill;
    struct  timeval ct;
    
    gettimeofday(&ct, NULL);
    if (data->start_time == 0)
        data->start_time = 1000 * (int)ct.tv_sec + (int)ct.tv_usec / 1000; 
    timeMill = (1000 * (int)ct.tv_sec + (int)ct.tv_usec / 1000) - data->start_time;
    
    return (timeMill);
}

void ft_error(char *s)
{
	printf("%s\n",s);
	exit(1);
}

void ft_malloc_error(void *allocated, t_data *data, int all)
{
    if (all == 1)
    {
        free(data->forks);
        data->forks = NULL;
        free(data->philos);
        data->philos = NULL;
    }
    else
    {
        free(allocated);
        allocated = NULL;
    }
	ft_error("Allocation error");
}

void ft_create_forks(t_data *data)
{
    int i;
    
    data->forks = malloc(data->nbr_of_philos * sizeof(pthread_mutex_t));
    if (!data->forks)
        ft_malloc_error(data->forks, data, 0);
    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_init(&data->forks[i], NULL);
}

