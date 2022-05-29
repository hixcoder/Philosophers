/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/05/29 10:19:04 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mails = 0;
int lock = 0;
pthread_mutex_t mutex;


void *routine() {
    for (int i = 0; i < 10000000; i++)
    {
        // the fun pthread_mutex_lock tell the program that if there is a thread excuting the line 25 
        // do not let any other thread excute that line after it finish  
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
}

int main()
{
    int j = 88;
    pthread_t th[j];
    int i;
    

    // initialize a mutex
    pthread_mutex_init(&mutex, NULL);
    
    i = -1;
    while (++i < j)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
            return (1);
        printf("thread %d has started\n", i);
    }

    i = -1;
     while (++i < j)
    {
        if (pthread_join(th[i], NULL) != 0)
            return (2);
        printf("thread %d has finished\n", i);
    }

    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n",mails);
     
    return (0);
}
