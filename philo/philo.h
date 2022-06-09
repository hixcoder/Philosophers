/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:38 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/09 13:08:38 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_philo
{
    pthread_t   philo_th;
    int         philo_id;
    int         eat_times;
    struct t_data      *data;

}   t_philo;

typedef struct s_data
{
    int             nbr_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             nbr_of_meals;
    int             start_time;
    t_philo         *philos;
    pthread_mutex_t *forks;
    
}   t_data;


void ft_parse_data(t_data *data, char **av);
void ft_create_forks(t_data *data);
void ft_malloc_error(void *allocated, t_data *data, int all);
void ft_error(char *s);
int ft_time(t_data *data);

void ft_take_rfork(t_data  *data, t_philo *philos);
void ft_take_lfork(t_data  *data, t_philo *philos);
void ft_eat(t_data  *data, t_philo *philos);
void ft_sleep_think(t_data  *data, t_philo *philos);
void ft_died(t_data  *data, t_philo *philos);


#endif