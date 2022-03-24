/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:37:59 by samajat           #+#    #+#             */
/*   Updated: 2022/03/24 16:18:55 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->argc - 2)
	{
		if (pipe(data->pipes[i]) < 0)
        {
            free_all_data(data);
            close_all (data);
			exit (1);
        }
		i++;
	}
	return (1);
}
