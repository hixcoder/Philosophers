/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:28:06 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/04 13:15:14 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_time()
{
    int     timeMill;
    struct  timeval current_time;
    
    gettimeofday(&current_time, NULL);
    timeMill = (int)current_time.tv_sec * 1000;
    return (timeMill);
}

void ft_error(char *s)
{
	printf("%s\n",s);
	exit(1);
}

void ft_malloc_error(void *allocated)
{
	free(allocated);
	ft_error("Allocation error");
}

void ft_create_forks(t_data *data)
{
    int i;
    
    data->forks = malloc(data->nbr_of_philos * sizeof(pthread_mutex_t));
    if (!data->forks)
        ft_malloc_error(data->forks);
    i = -1;
    while (++i < data->nbr_of_philos)
        pthread_mutex_init(&data->forks[i], NULL);
}

