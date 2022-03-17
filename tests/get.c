/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:58:59 by samajat           #+#    #+#             */
/*   Updated: 2022/03/17 17:35:08 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main ()
{
	char *text;
	char *str;
    char limit[] = "li";

	str = ft_strdup("");
	text = ft_strdup("");
	while (ft_memcmp(limit, str, ft_strlen(limit)))
	{
		text = ft_strjoin(text, str);
		str = get_next_line(0);
	}
    printf("%s", text);
}