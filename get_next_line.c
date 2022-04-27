/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:37:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/26 19:38:10 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*container;
	char		*buff;
	char		*split_ptr;
	char		*tmp_container;
	char		*tmp_buff;
	char		*str;
	int		size;
	int	bytes_read;

	str = NULL;
	while (ft_strchr(container, '\n') == NULL)
	{
		buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1 || bytes_read == 0) //TODO free when -1
		{
			free(buff);
			break ;
		}
		buff[bytes_read] = '\0';
		if (container == NULL)
			container = ft_strdup("");
		tmp_container = container;
		container = ft_strjoin(container, buff);
		free(tmp_container);
		free(buff);
		if (bytes_read < BUFFER_SIZE)
			break ;
	}
	split_ptr = ft_strchr(container, '\n');
	if (split_ptr != NULL)
	{
		tmp_buff = ft_strdup(container);
		size = split_ptr - container;
		tmp_buff[size + 1] = '\0';
		str = ft_strdup(tmp_buff);
		free(tmp_buff);
		tmp_container = container;
		container = ft_strdup(split_ptr + 1);
		free(tmp_container);
	}
	else
	{
		if (container != NULL)
		{
			str = ft_strdup(container);
			free(container);
			container = NULL;
		}
	}
	return (str);
}
