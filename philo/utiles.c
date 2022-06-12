/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:28:06 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/11 11:44:00 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ct: is the current time
int ft_current_time(t_data *data)
{
    int     timeMill;
    struct  timeval ct;
    
    gettimeofday(&ct, NULL);
    if (data->start_time == 0)
        data->start_time = 1000 * (int)ct.tv_sec + (int)ct.tv_usec / 1000; 
    timeMill = (1000 * (int)ct.tv_sec + (int)ct.tv_usec / 1000) - data->start_time;
    
    return (timeMill);
}

int ft_error(char *s)
{
	printf("%s\n",s);
	return (ERROR);
}

void ft_clean(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_destroy(&data->forks[i]);
    i = -1;
    free(data->isforks_used);
    data->isforks_used = NULL;
    free(data->forks);
    data->forks = NULL;
    free(data->philos);
    data->philos = NULL;
}

void ft_malloc_error(void *allocated, t_data *data, int all)
{
    if (all == 1)
        ft_clean(data);
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
    data->isforks_used = malloc(data->nbr_of_philos * sizeof(int));
    if (!data->forks || !data->isforks_used)
        ft_malloc_error(data->forks, data, 0);
    pthread_mutex_init(&data->death_mutex, NULL);
    i = -1;
    while (++i < data->nbr_of_philos){
        pthread_mutex_init(&data->forks[i], NULL);
        data->isforks_used[i] = 0;
    }
}

