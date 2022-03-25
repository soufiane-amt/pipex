/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 20:37:00 by samajat           #+#    #+#             */
/*   Updated: 2022/03/23 20:20:59 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	**allocate_arr(int argc)
{
	int	**pipes;
	int	i;

	i = -1;
	pipes = malloc(sizeof(int *) * (argc - 2));
	if (!pipes)
		exit(1);
	while (++i < argc - 2)
	{
		pipes[i] = malloc(sizeof(int) * (2));
		if (!pipes[i])
		{
			t_free(pipes, i);
			exit(1);
		}
	}
	return (pipes);
}
