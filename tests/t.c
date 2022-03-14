/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:34:06 by samajat           #+#    #+#             */
/*   Updated: 2022/03/10 14:52:46 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../includes/pipex.h"
#include <stddef.h>

int main ()
{
    char name[10];
    printf ("HI\n");
    ft_putstr_fd ("First name :", 0);
    read (0, name, 10);
    ft_putstr_fd ("Second name :", 0);
    read (0, name, 10);
    ft_putstr_fd ("Phone number :", 0);
    read (0, name, 10);
    ft_putstr_fd ("Address :", 0);
    read (0, name, 10);
    return (0);
}