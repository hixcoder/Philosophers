/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:28:06 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/16 17:22:54 by ubunto           ###   ########.fr       */
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
        data->start_time = (1000 * ct.tv_sec + ct.tv_usec / 1000); 
    timeMill =(int)(1000 * ct.tv_sec + ct.tv_usec / 1000 - data->start_time);
    return (timeMill);
}

int ft_check_before_eat(t_data  *data, t_philo *philo)
{
    while (philo->eat_times == 0)
    {
        if (ft_current_time(data) >= data->time_to_die)
	    	return (0);
    }
    return (1);
}

void	ft_msleep(int sleep_ms, t_data *data)
{
	int	end_time;
    // int i;
    
    // i = -1;
	end_time = ft_current_time(data) + sleep_ms;
	while (ft_current_time(data) < end_time && data->death_status == 0)
	// while (ft_current_time(data) < end_time)
        usleep(10);
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
    pthread_mutex_destroy(&data->death_mutex);
    pthread_mutex_unlock(&data->print_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    i = -1;
    free(data->forks);
    data->forks = NULL;
    free(data->philos);
    data->philos = NULL;
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
