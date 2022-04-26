/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:37:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/26 13:20:29 by hiyamamo         ###   ########.fr       */
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
	char	*tmp_container;
	int			i;
	int			k;
	
	// first look at container;
	i = 0;
	if (container != NULL)
	{
		while (container[i] != '\0')
		{
			if (container[i] == '\n')
			{
				str = (char *) malloc(i + 2);
				if (str == NULL)
				{
					free(container);
					return (NULL);
				}
				i++;
				str[i--] = '\0';
				k = 0;
				while (k <= i)
				{
					str[k] = container[k];
					k++;
				}
				container = &container[k];
				return (str);
			}
			i++;
		}
	}
	if (container != NULL) // check if I should put NULL to container
		str = ft_strdup(container); 

	// first read
	buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
	{
		if (container != NULL)
			free(container);
		return (NULL);
	}
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(buff);
		if (container != NULL)
			free(container);
		return (NULL);
	}
	if (bytes_read == 0)
	{
		str = NULL;
		if (container != NULL)
		{
			str = ft_strdup(container);
			container = NULL;
		}
		return (str);
	}
	buff[bytes_read] = '\0';
	
	// check if \n is included
	if (ft_strchr(buff, '\n') == NULL)
	{
		i = 0;
		while (ft_strchr(buff, '\n') == NULL)
		{
			if (i == 0 && container == NULL)
				str = ft_strdup(buff);
			else
			{
				prev_str = str;
				str = ft_strjoin(prev_str, buff);
				free(prev_str);
			}
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
			i++;
		}
		i = 0;
		while (buff[i] != '\0')
		{
			if(buff[i++] == '\n')
			{
				container = ft_strdup(&buff[i]);
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
		tmp_container = container;
		i = 0;
		while (buff[i] != '\0')
		{
			if(buff[i++] == '\n')
			{
				container = ft_strdup(&buff[i]);
				buff[i] = '\0';
			}
		}
		if (tmp_container != NULL)
		{
			str = ft_strjoin(tmp_container, buff);
			free(tmp_container);
		}
		else
			str = ft_strdup(buff);
	}
	return (str);
}
