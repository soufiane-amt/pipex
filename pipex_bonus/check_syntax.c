/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:46:14 by samajat           #+#    #+#             */
/*   Updated: 2022/03/19 21:31:55 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int check_syntax(t_data *data)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 2;
	result = 0;
	result |= access(data ->argv[1], F_OK);
	generate_paths(data, data -> env);
	while (j < data->argc - 1)
	{
		data -> cmd = ft_split (data -> argv[j], ' ');
		while (data->all_paths[j])
		{
			data->all_paths[j] = ft_strjojn (data->all_paths[j], "/");
			data->mypath = ft_strjojn (data->all_paths[j], data->cmd[0]);
			result |= access (data->mypath, F_OK);
			j++;
		}
	}
	return (result);
}