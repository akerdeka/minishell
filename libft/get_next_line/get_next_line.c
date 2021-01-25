/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:05:34 by pbesson           #+#    #+#             */
/*   Updated: 2021/01/22 16:14:09 by wasayad          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_strlen_line(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_read(int fd, char *str, int *ret)
{
	char *buf;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while ((*ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (*ret < 0)
		{
			ft_strdel(str);
			ft_strdel(buf);
			return (NULL);
		}
		buf[*ret] = '\0';
		if (ft_strchr(buf, '\n'))
		{
			if (!(str = ft_strjoin(str, buf)))
				return (NULL);
			ft_strdel(buf);
			return (str);
		}
		if (!(str = ft_strjoin(str, buf)))
			return (NULL);
	}
	ft_strdel(buf);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char	*storage = NULL;
	char		*str;
	int			ret;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	if (!(str = ft_strdup("")))
		return (-1);
	if (storage != NULL && (ft_strchr(storage, '\n')))
		return (ft_norme(&(*line), &str, &storage));
	if (storage != NULL)
	{
		ft_strdel(str);
		if (!(str = ft_read(fd, storage, &ret)))
			return (-1);
	}
	else
	{
		ft_strdel(str);
		if (!(str = ft_read(fd, str, &ret)))
			return (-1);
	}
	return (ft_norme_2(&ret, &(*line), &str, &storage));
}

int		ft_norme(char **line, char **str, char **storage)
{
	if (!(*line = ft_substr(*storage, 0, ft_strlen_line(*storage))))
		return (-1);
	ft_strdel(*str);
	if (!(*str = ft_strdup(*storage)))
		return (-1);
	ft_strdel(*storage);
	if (!(*storage = ft_strdup(ft_strchr(*str, '\n') + 1)))
		return (-1);
	ft_strdel(*str);
	return (1);
}

int		ft_norme_2(int *ret, char **line, char **str, char **storage)
{
	if (*ret == 0)
	{
		if (!(*line = ft_strdup(*str)))
			return (-1);
		ft_strdel(*storage);
		return (0);
	}
	if (!(*line = ft_substr(*str, 0, ft_strlen_line(*str))))
		return (-1);
	ft_strdel(*str);
	return (1);
}
