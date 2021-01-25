/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:01:15 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:24:08 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int		ft_check_char(char *set, char c)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

static	int		ft_check_to_right(char *str, char *set)
{
	int i;

	i = 0;
	while (str[i] && ft_check_char(set, str[i]) == 0)
		i++;
	return (i);
}

static	int		ft_check_to_left(char *str, char *set)
{
	int i;

	i = 0;
	while (str[i + 1])
		i++;
	while (i > 0 && (ft_check_char(set, str[i]) == 0))
		i--;
	return (i);
}

static	char	*ft_void_str(void)
{
	char *str;

	if (!(str = malloc(sizeof(char) * 1)))
		return (0);
	str[0] = '\0';
	return (str);
}

char			*ft_strtrim_free(char *str, char const *set)
{
	char	*dst;
	int		size_to_right;
	int		size_to_left;
	int		size_dst;
	int		i;

	if (str[0] == '\0')
		return ((char *)str);
	size_to_right = ft_check_to_right((char *)str, (char *)set);
	size_to_left = ft_check_to_left((char *)str, (char *)set);
	size_dst = (size_to_left - size_to_right + 1);
	i = 0;
	if (str[size_to_right] == '\0')
		return (ft_void_str());
	if (!(dst = malloc(sizeof(char) * (size_dst + 1))))
		return (0);
	while (size_to_right <= size_to_left)
	{
		dst[i] = str[size_to_right];
		size_to_right++;
		i++;
	}
	dst[i] = '\0';
	ft_strdel(str);
	return (dst);
}
