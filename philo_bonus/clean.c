/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:38:58 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/23 15:54:17 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_close(data->done_sem);
	sem_close(data->finish_eat_sem);
	free(data->philos);
	data->philos = NULL;
	free(data->pids);
	data->pids = NULL;
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
