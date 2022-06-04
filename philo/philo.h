/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:38 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/04 13:18:07 by hboumahd         ###   ########.fr       */
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
    int         eat_time;

}   t_philo;

typedef struct s_data
{
    int             nbr_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             nbr_of_meals;
    t_philo         *philos;
    pthread_mutex_t *forks;
    
}   t_data;


void ft_parse_data(t_data *data, char **av);
void ft_create_forks(t_data *data);
void ft_malloc_error(void *allocated);
void ft_error(char *s);
int ft_time();

#endif