/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:46:14 by samajat           #+#    #+#             */
/*   Updated: 2022/03/23 20:40:18 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}


void	add_slash_to_paths(t_data *data)
{
	int		i;
	char	*str;

	i = 1;
	while (data->all_paths[++i])
	{
		str = data->all_paths[i];
		data->all_paths[i] = ft_strjoin (str, "/");
		free(str);
	}
}

int	check_syntax(t_data *data)
{
	int		i;
	int		j;
	int		cmd_found;
	int		result;

	i = 1;
	j = -1;
	if(access(data ->argv[1], F_OK)== -1)
        print_error("Input file dosn't exist .");
	generate_paths(data, data -> env);
	add_slash_to_paths(data);
	while (++i < data->argc - 1)
	{
		data -> cmd = ft_split (data -> argv[i], ' ');
		cmd_found = -1;
		j = -1;
		while (data->all_paths[++j] && cmd_found == -1)
		{
			data->mypath = ft_strjoin (data->all_paths[j], data->cmd[0]);
			cmd_found &= access (data->mypath, F_OK);
			free(data->mypath);
		}
		result |= cmd_found;
		free_arr(data->cmd);
	}
	return (result);
}
