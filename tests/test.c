/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:38:13 by samajat           #+#    #+#             */
/*   Updated: 2022/03/10 21:05:56 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main ()
{
    int num[2];
    int n;
    int result;
    int i;
    
    i = 0;
    n = 1337;
    pipe (num);
    while (i < 10)
    {
        write (num[1], &n, sizeof(int));
        n++;
        i++;
    }
    while (i)
    {
        read(num[0], &n, sizeof(int));
        printf ("%d ", n);
        i--;
    }
    
}