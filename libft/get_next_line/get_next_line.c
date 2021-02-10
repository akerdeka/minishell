/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharras <acharras@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:59:39 by akerdeka          #+#    #+#             */
/*   Updated: 2021/02/09 15:58:19 by acharras         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_read_norme(char *buff, char **str, char *temp)
{
	if (!(temp = ft_strdup(*str)))
		return (-1);
	free(*str);
	if (!(*str = ft_strjoin(temp, buff)))
		return (-1);
	free(temp);
	free(buff);
	return (1);
}

int		ft_read(int fd, char **str)
{
	int		ret;
	char	*buff;
	char	*temp;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buff[ret] = '\0';
		if (ft_strchr(buff, '\n'))
		{
			if (ft_read_norme(buff, str, temp) == 1)
				return (1);
			return (-1);
		}
		if (!(temp = ft_strdup(*str)))
			return (-1);
		free(*str);
		if (!(*str = ft_strjoin(temp, buff)))
			return (-1);
	}
	free(buff);
	return (0);
}

int		ft_fill(int fd, char **str, char **line)
{
	int			ret;
	char		*temp;

	if ((ret = ft_read(fd, str)) == -1)
		return (-1);
	if (ret != 0)
	{
		if (!(*line = ft_substr(*str, 0, ft_strchr(*str, '\n') - *str)))
			return (-1);
		if (!(temp = ft_strdup(ft_strchr(*str, '\n') + 1)))
			return (-1);
		free(*str);
		*str = temp;
		return (1);
	}
	else
	{
		if (!(*line = ft_substr(*str, 0, ft_strchr(*str, '\0') - *str)))
			return (-1);
		free(*str);
		*str = NULL;
		return (0);
	}
}

int		get_next_line_norme(char **str, char **line)
{
	char	*temp;

	if (!(*line = ft_substr(*str, 0, ft_strchr(*str, '\n') - *str)))
		return (-1);
	if (!(temp = ft_strdup(ft_strchr(*str, '\n') + 1)))
		return (-1);
	free(*str);
	*str = temp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*str = NULL;
	int			ret;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	if (str == NULL)
		if (!(str = ft_strdup("")))
			return (-1);
	if (!(ft_strchr(str, '\n')))
	{
		if ((ret = ft_fill(fd, &str, line)) <= 0)
		{
			free(str);
			return (ret == -1 ? -1 : 0);
		}
		return (1);
	}
	else
	{
		if (get_next_line_norme(&str, line) == 1)
			return (1);
		return (-1);
	}
	free(str);
	return (0);
}
