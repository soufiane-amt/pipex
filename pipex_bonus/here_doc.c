/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:25:07 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 19:36:21 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    open_here_doc(t_data *data)
{
    int temp;
    char    *str;
    int     delimiter_size;

    str = ft_strdup("");
    delimiter_size = ft_strlen(data->argv[2]) - 1;
    temp = open(".temp", O_CREAT | O_RDWR | O_APPEND, 0777);
    while (ft_memcmp(str, data->argv[2], delimiter_size))
    {
        ft_putstr_fd(str, temp);
        str = get_next_line(0);
    }
}

int    add_here_doc(t_data *data)
{
    if (ft_memcmp(data->argv[1], "here_doc", 8))
    {
        data->is_here_doc = 0;
        return (0);
    }
    data->is_here_doc = 1;
    open_here_doc(data);
    return(1);
}