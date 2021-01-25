/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:18:50 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:23:44 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	dst_size;
	size_t			i;

	dst_size = ft_strlen(dst);
	i = 0;
	if (dst_size > size)
		return (ft_strlen(src) + size);
	while (size - dst_size > 1 && src[i])
	{
		dst[dst_size + i] = src[i];
		size--;
		i++;
	}
	dst[dst_size + i] = '\0';
	return (ft_strlen(src) + dst_size);
}
