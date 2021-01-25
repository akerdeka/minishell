/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove_chr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:25:16 by pbesson           #+#    #+#             */
/*   Updated: 2020/03/04 12:04:09 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strremove_chr(char *src, char c)
{
	int		i;
	int		j;
	int		size;
	char	*dst;

	i = -1;
	j = 0;
	size = 0;
	while (src[++i])
		if (src[i] != c)
			size++;
	if (!(dst = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	i = -1;
	while (src[++i])
	{
		if (src[i] != c)
		{
			dst[j] = src[i];
			j++;
		}
	}
	dst[j] = '\0';
	ft_strdel(src);
	return (dst);
}
