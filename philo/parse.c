/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:28:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/23 23:12:59 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (str[i] == '-')
		return (ERROR);
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + (str[i++] - '0');
		else
			return (ERROR);
	}
	if (nbr > 2147483647)
		return (ERROR);
	return ((int) nbr);
}

int	ft_parse_data(t_data *data, char **av)
{
	data->nbr_of_philos = ft_atoi(av[1]);
	if (data->nbr_of_philos <= 0)
		return (ERROR);
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die == ERROR)
		return (ERROR);
	data->time_to_eat = ft_atoi(av[3]);
	if (data->time_to_eat == ERROR)
		return (ERROR);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep == ERROR)
		return (ERROR);
	if (av[5] != NULL)
		data->nbr_of_meals = ft_atoi(av[5]);		
	else
		data->nbr_of_meals = -2;
	if (data->nbr_of_meals == ERROR)
		return (ERROR);
	data->start_time = 0;
	data->death_status = 0;
	data->philos_finished_eating = 0;
	return (SUCCESS);
}
