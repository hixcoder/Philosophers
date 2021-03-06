/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:38 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/24 10:48:55 by hboumahd         ###   ########.fr       */
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
# include <fcntl.h> 
# include <semaphore.h>
# include <signal.h>

# define ERROR -1
# define SUCCESS 0

typedef struct s_philo
{
	pthread_t		philo_th;
	int				philo_id;
	int				eat_times;
	int				time_of_last_eat;
	int				lfork;
	int				rfork;
	struct t_data	*data;

}	t_philo;

typedef struct s_data
{
	int				nbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	long long		start_time;
	int				*pids;
	sem_t			*print_sem;
	t_philo			*philos;
	sem_t			*forks_sem;
	sem_t			*done_sem;
	sem_t			*finish_eat_sem;
}	t_data;

void	ft_parse_data(t_data *data, char **av, int ac);

void	ft_clean(t_data *data);
void	ft_error(char *s);
void	ft_malloc_error(t_data *data, char *message);

long	ft_current_time(t_data *data);
void	ft_msleep(int sleep_ms, t_data *data);
void	ft_is_died(t_philo	*philo);
void	ft_wait(t_data *data);

void	ft_take_rfork(t_data *data, t_philo *philos);
void	ft_take_lfork(t_data *data, t_philo *philos);
void	ft_eat(t_data *data, t_philo *philos);
void	ft_sleep_think(t_data *data, t_philo *philos);

void	ft_create_forks(t_data *data);
void	*routine(void *arg);
void	ft_create_philos(t_data *data);

#endif