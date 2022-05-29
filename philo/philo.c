/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:46:35 by hboumahd          #+#    #+#             */
/*   Updated: 2022/05/29 10:38:00 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

int mails = 0;
int lock = 0;
pthread_mutex_t mutex;


void *role_dice() {
    int value;
    int *res;

    pthread_mutex_lock(&mutex);
    value = (rand() % 6) + 1;
    res = malloc(sizeof(int));
    *res = value;
    printf("this is the adress of res in the fun: %p\n", res);
    pthread_mutex_unlock(&mutex);
    return (res);
}

int main()
{
    int j = 4;
    pthread_t th[j];
    int i;
    int *res;
    

    // initialize a mutex
    pthread_mutex_init(&mutex, NULL);
    
    i = -1;
    while (++i < j)
    {
        if (pthread_create(&th[i], NULL, &role_dice, NULL) != 0)
            return (1);
        printf("thread %d has started\n", i);
    }

    i = -1;
     while (++i < j)
    {
        if (pthread_join(th[i],(void **) &res) != 0)
            return (2);
        printf("thread %d has finished whit ==> %d\n", i, *res);
        printf("this is the adress of res in the main: %p\n", res);

        free(res);
    }
    pthread_mutex_destroy(&mutex);
     
    return (0);
}
