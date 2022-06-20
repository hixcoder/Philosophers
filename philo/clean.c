/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:38:58 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/20 09:40:05 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_clean(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_unlock(&data->forks[i]);
    while (++i < data->nbr_of_philos)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->death_mutex);
    pthread_mutex_unlock(&data->print_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    i = -1;
    free(data->forks);
    data->forks = NULL;
    free(data->philos);
    data->philos = NULL;
}

int ft_error(char *s)
{
	printf("%s\n",s);
	return (ERROR);
}

int ft_malloc_error(void *allocated, t_data *data, int all)
{
    if (all == 1)
        ft_clean(data);
    else
    {
        free(allocated);
        allocated = NULL;
    }
	return (ft_error("Allocation error"));
}
