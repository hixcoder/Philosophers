/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/05/30 11:49:43 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

void *routine()
{
   
   return (NULL);
}

int main(int ac, char **av)
{
    t_philos philos;
    
    if (ac >= 5 && ac <= 6)
    {
        ft_init_philos(&philos, av);
    }
    else
    {
        printf("=> Please Enter: ./philo [nbr_of_philos] [time_to_die]");
        printf("[time_to_eat] [time_to_sleep] [nbr_of_meals]\n");
        printf("=> this is optional: [nbr_of_meals]\n");
    }
    return (0);
}
