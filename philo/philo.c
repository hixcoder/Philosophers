/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/05/29 13:08:20 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

pthread_mutex_t mutex;

// ================= Difference between trylock and lock in C   =================  
// pthread_mutex_trylock is instant ==> if you are not lock then lock , and if you are lock then ok I will excute the rest of the code
// pthread_mutex_lock is always waiting ==> if you are not lock then lock, and if you are lock then wait until you unlock then excute the rest of the code 

void *routine()
{
   if (pthread_mutex_trylock(&mutex) == 0)
   {
       printf("Got lock\n");
       sleep(1);
       pthread_mutex_unlock(&mutex);
   }
   else
   {
       printf("Didn't get lock\n");
   }
   return (NULL);
}

int main()
{
    int j = 4;
    pthread_t th[j];
    int i;

    i = -1;
    pthread_mutex_init(&mutex, NULL);
    while(++i < j)
    {
        if(pthread_create(&th[i], NULL, &routine, NULL))
            return (1);
    }
    
    i = -1;
    while (++i < j)
    {
        if (pthread_join(th[i], NULL))
            return (2);
    }
    pthread_mutex_destroy(&mutex);
    return (0);
}
