/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 17:28:13 by samajat           #+#    #+#             */
/*   Updated: 2022/03/14 17:32:39 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    show_content_file (int fd)
{
    char    *str;

    str = ft_strdup ("");
    while (str)
    {
        printf ("%s", str);
        str = get_next_line (fd);
    }
}