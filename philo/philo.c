/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/05/28 18:32:28 by hboumahd         ###   ########.fr       */
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
    pthread_t t1;
    pthread_t t2;
    

    // initialize a mutex
    pthread_mutex_init(&mutex, NULL);
    
    // for initialize a thread use create
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        return (1);
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        return (2);
        
    // for wait until excution
    if (pthread_join(t1, NULL) != 0)
        return (3);
    
    if (pthread_join(t2, NULL) != 0)
        return (4);
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n",mails);
    return (0);
}
