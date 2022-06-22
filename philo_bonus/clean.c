/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:38:58 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/22 12:13:04 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_data *data)
{
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	free(data->philos);
	data->philos = NULL;
	// pthread_mutex_unlock(&data->print_mutex);
	// pthread_mutex_destroy(&data->print_mutex);
}

void	ft_error(char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

void	ft_malloc_error(void *allocated)
{
	free(allocated);
	allocated = NULL;
	ft_error("Allocation error");
}
