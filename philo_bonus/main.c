/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/22 17:20:07 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// => Please Enter: ./philo [nbr_of_philos] [time_to_die] [time_to_eat]
//					[time_to_sleep] [nbr_of_meals]
// => [nbr_of_meals] is optional

int	main(int ac, char **av)
{
	t_data	data;

	if (ac >= 5 && ac <= 6)
	{
		ft_parse_data(&data, av);
		ft_create_forks(&data);
		ft_create_philos(&data);
		ft_wait(&data);
		ft_clean(&data);
	}
	else
		ft_error("Invalid Arguments");
	return (SUCCESS);
}
