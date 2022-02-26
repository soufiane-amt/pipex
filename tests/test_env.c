/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:07:13 by samajat           #+#    #+#             */
/*   Updated: 2022/02/26 18:08:48 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../includes/pipex.h"

int main (int argc, char **argv, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        printf ("%s\n", env[i]);
        i++;
    }
}