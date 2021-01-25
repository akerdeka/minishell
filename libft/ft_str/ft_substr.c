/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:23:05 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:24:14 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
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
	return (dst);
}
