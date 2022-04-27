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

int	read_with_container(int fd, char **container)
{
	char	*buff;
	char	*tmp_container;
	int		bytes_read;

	buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read == -1 || bytes_read == 0)
	{
		free(buff);
		return (0);
	}
	buff[bytes_read] = '\0';
	if (*container == NULL)
		*container = ft_strdup(buff);
	else
	{
		tmp_container = *container;
		*container = ft_strjoin(*container, buff);
		free(tmp_container);
	}
	free(buff);
	if (bytes_read < BUFFER_SIZE)
		return (0);
	return (1);
}

char	*update_str_and_container(char *split_ptr, char **container, char *str)
{
	char	*tmp_container;
	char	*tmp_buff;

	tmp_buff = ft_strdup(*container);
	tmp_buff[(split_ptr - *container) + 1] = '\0';
	str = ft_strdup(tmp_buff);
	free(tmp_buff);
	tmp_container = *container;
	*container = ft_strdup(split_ptr + 1);
	if (**container == '\0')
	{
		free(*container);
		*container = NULL;
	}
	free(tmp_container);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*split_ptr;
	char		*str;

	str = NULL;
	while (ft_strchr(container, '\n') == NULL)
		if (read_with_container(fd, &container) == 0)
			break ;
	split_ptr = ft_strchr(container, '\n');
	if (split_ptr != NULL)
		str = update_str_and_container(split_ptr, &container, str);
	else
		if (container != NULL)
		{
			str = ft_strdup(container);
			free(container);
			container = NULL;
		}
	return (str);
}
