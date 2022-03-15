/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:46:05 by samajat           #+#    #+#             */
/*   Updated: 2022/03/15 13:16:17 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//Headers
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../srcs/get_next_line/get_next_line.h"

//data
typedef struct s_data
{
    int		id;
	char	*path;
	char	**all_paths;
	char	*mypath;
	char	**cmd;
	int		infile;
	int		outfile;
}   t_data;


//utils
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int     ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
void    show_content_file (int fd);

#endif