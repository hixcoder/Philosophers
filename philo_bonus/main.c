/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboumahd <hboumahd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:15:53 by hboumahd          #+#    #+#             */
/*   Updated: 2022/06/21 11:40:23 by hboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_NUM 4

// how to use fork function
int main()
{
    int id1;
    int id2;
    int id;

    id1 = fork();
    // if (id1 != getpid())
    //     printf("main process = %d\n", getpid());
    if (id1 != 0)
    {
        printf("id1 = %d\n", id1);
        id2 = fork();
        if (id2 != 0)
            printf("id2 = %d\n", id2);
    }
    return (0);
}