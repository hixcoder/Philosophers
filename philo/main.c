/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubunto <ubunto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/13 11:45:15 by ubunto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// => Please Enter: ./philo [nbr_of_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_of_meals]
// => [nbr_of_meals] is optional

int main(int ac, char **av)
{
    t_data  data;
    int     status;
    
    if (ac >= 5 && ac <= 6)
    {
        if (ft_parse_data(&data, av) == ERROR)
            return (ft_error("Invalid Arguments"));
        ft_create_forks(&data);
        status = ft_create_philos(&data);
        ft_clean(&data);
    }
    else
        status = ft_error("Invalid Arguments");
    return (status);
}
