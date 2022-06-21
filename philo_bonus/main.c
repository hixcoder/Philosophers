/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:15:53 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/20 22:40:51 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_NUM 4

sem_t *sema;

void *routine(void *args)
{
    int i = 1;
    i++;
    sem_wait(sema);
    usleep(1000);
    printf("hello from thread %d\n", *(int *)args);
    sem_post(sema);
    free(args); 
}

int main()
{
    int i;
    int *a;
    pthread_t th[THREAD_NUM];
    
    // init the semaphore
    // sem_init(&semaphore, 0, 1);
    sem_unlink("sem_forks");
    sema = sem_open("sem_forks", O_CREAT, 0644, 5);
    int x = 0;
    for(i = 0; i < THREAD_NUM;  i++)
    {
        a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            perror("failed to create thread");
    }
    for(i = 0; i < THREAD_NUM;  i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("failed to create thread");
    }
    // destroy the semaphore
    sem_close(sema);
    return (0);
}