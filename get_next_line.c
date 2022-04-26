/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:37:35 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/04/26 19:23:20 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



#include <stdio.h>


char	*read_from_container(char **container)
{
	char	*str;
	char	*tmp_container;
	int		i;
	int		k;

	i = 0;
	while (container[0][i] != '\0')
	{
		if (container[0][i] == '\n')
		{
			str = (char *) malloc((i++ + 2) * sizeof(char));
			if (str == NULL)
			{
				free(container[0]);
				return (NULL) ;
			}
			str[i--] = '\0';
			k = 0;
			while (k <= i)
			{
				str[k] = container[0][k];
				k++;
			}
			tmp_container = *container; //TODO have issue for free
			*container = ft_strdup(&(container[0][k]));
			free(tmp_container);
			tmp_container = NULL;
			return (str);
		}
		i++;
	}
	str = ft_strdup(*container);
	return (str);
}

char	*first_read(int fd, char **container)
{
	char	*buff;
	int		bytes_read;
	
	printf("*container:%s\n", *container);

	buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
	{
		if (*container != NULL)
			free(*container);
		return (NULL);
	}
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read == -1 || bytes_read == 0)
	{
		free(buff);
		printf("---- *container:%s\n", *container);
		if (*container != NULL)
			free(*container); //TODO error happen
		return (NULL);
	}
	buff[bytes_read] = '\0';
	return (buff);
}

char	*read_more(int fd, char **container, char *buff, char *str)
{
	char	*prev_str;
	int		bytes_read;
	int		i;

	while (ft_strchr(buff, '\n') == NULL)
	{
		if (str == NULL)
			str = ft_strdup("");
		prev_str = str;
		str = ft_strjoin(prev_str, buff);
		free(prev_str);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL); // free
		if (bytes_read == 0)
		{
			free(buff);
			free(*container);
			*container = NULL;
			return (str);
		}
		buff[bytes_read] = '\0';
	}
	i = 0;
	while (buff[i] != '\0')
	{
		if(buff[i++] == '\n')
		{
			free(*container);
			*container = ft_strdup(&buff[i]);
			buff[i] = '\0';
		}
	}
	prev_str = str;
	str = ft_strjoin(prev_str, buff);
	free(prev_str);
	free(buff);
	return (str);
}

char	*make_str_from_first_read(char **container, char *buff)
{
	char	*tmp_container;
	char	*str;
	int		i;

	tmp_container = *container;
	i = 0;
	while (buff[i] != '\0')
	{
		if(buff[i++] == '\n')
		{
			*container = ft_strdup(&buff[i]);
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
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*str;
	char		*buff;

	str = NULL;
	if (container != NULL)
	{
		str = read_from_container(&container);
		if (ft_strchr(str, '\n') != NULL)
			return (str);
	}
	buff = first_read(fd, &container);
	if (buff == NULL)
		return (str);
	if (ft_strchr(buff, '\n') == NULL)
		str = read_more(fd, &container, buff, str);
	else
		str = make_str_from_first_read(&container, buff);
	printf("con:%s\n", container);
	return (str);
}
