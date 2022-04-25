/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:37:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/25 20:53:53 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*buff;
	int			bytes_read;
	char		*prev_str;
	char		*str;
	static char	*container;
	int			i;
	int			k;
	
	str = (char *) malloc(1);
	str[0] = '\0';

	// first look at container;
	i = 0;
	if (container != NULL)
	{
		while (container[i] != '\0')
		{
			if (container[i] == '\n')
			{
				free(str);
				str = (char *) malloc(i + 1);
				str[i--] = '\0';
				k = 0;
				while (i >= 0)
					str[i--] = container[k++];
				return (str);
			}
			i++;
		}
		str = ft_strjoin(str, container);
	}

	// first read
	buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	buff[bytes_read] = '\0';
	if (bytes_read == 0 || bytes_read == -1)
	{
		free(buff);
		return (NULL);
	}

	if (ft_strchr(buff, '\n') == NULL)
	{
		while (ft_strchr(buff, '\n') == NULL)
		{
			prev_str = str;
			str = ft_strjoin(prev_str, buff);
			free(prev_str);
			bytes_read = read(fd, buff, BUFFER_SIZE);
			buff[bytes_read] = '\0';
			if (bytes_read == 0)
				return (str);
			if (bytes_read < BUFFER_SIZE)
			{
				buff[bytes_read] = '\0';
				prev_str = str;
				str = ft_strjoin(prev_str, buff);
				free(prev_str);
				free(buff);
				return (str);
			}
		}
		i = 0;
		while (buff[i] != '\0')
		{
			if(buff[i++] == '\n')
			{
				container = ft_strjoin("", &buff[i]);
				buff[i] = '\0';
			}
		}
		prev_str = str;
		str = ft_strjoin(prev_str, buff);
		free(prev_str);
		free(buff);
	}
	else
	{
		str = NULL;
	}

	printf("container: %s\n", container);
	return (str);
}
//TODO: check static var
