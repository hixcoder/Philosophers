/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:28:55 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/24 10:43:18 by hboumahd         ###   ########.fr       */
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
		ft_error("Invalid Arguments");
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + (str[i++] - '0');
		else
			ft_error("Invalid Arguments");
	}
	if (nbr > 2147483647)
		ft_error("Invalid Arguments");
	return ((int) nbr);
}

void	ft_parse_data(t_data *data, char **av, int ac)
{
	struct timeval	ct;

	if (ac < 5 || ac > 6)
		ft_error("Invalid Arguments");
	data->nbr_of_philos = ft_atoi(av[1]);
	if (data->nbr_of_philos <= 0)
		ft_error("Invalid Arguments");
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
		data->nbr_of_meals = ft_atoi(av[5]);
	else
		data->nbr_of_meals = -1;
	data->start_time = 0;
	gettimeofday(&ct, NULL);
	data->start_time = (1000 * ct.tv_sec + ct.tv_usec / 1000);
}
