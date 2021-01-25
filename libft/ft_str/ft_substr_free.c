/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 20:30:09 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:24:11 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr_free(char *src, unsigned int start, size_t len)
{
	char	*dst;
	int		i;

	i = 0;
	if (start > ft_strlen(src))
		len = 0;
	if (len > ft_strlen(src + start))
		len = ft_strlen(src + start);
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (len)
	{
		dst[i++] = src[start];
		len--;
		start++;
	}
	dst[i] = '\0';
	ft_strdel(src);
	return (dst);
}
