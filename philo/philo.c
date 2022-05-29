/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/05/29 11:27:37 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
    int i;

    i = *(int *)arg;
    printf("value of prime in thread %d is %d \n", i, primes[i]);
    free(arg);
    return (NULL);
}

int main()
{
    int j = 2;
    pthread_t th[j];
    int i;
    int *a;

    i = -1;
    while (++i < j)
    {
        a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            return (1);
    }

    i = -1;
    while (++i < j)
    {
        if (pthread_join(th[i], NULL) != 0)
            return (2);
    }
    return (0);
}
