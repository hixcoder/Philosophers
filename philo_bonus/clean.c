/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:38:58 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/22 17:53:45 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill(t_data *data)
{
	int i;
	
	i = -1;
	while(++i < data->nbr_of_philos)
		kill(data->pids[i], SIGTERM);
}

void	ft_clean(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	free(data->philos);
	data->philos = NULL;
	free(data->pids);
	data->pids = NULL;
	// pthread_mutex_unlock(&data->print_mutex);
	// pthread_mutex_destroy(&data->print_mutex);
}

void	ft_error(char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

void	ft_malloc_error(t_data *data, char *message)
{
	ft_clean(data);
	ft_error(message);
}
