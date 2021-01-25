/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:21:46 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:21:47 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	const char *s;

	s = src;
	if (src == NULL)
		return (0);
	while (n)
	{
		if (*s == c)
			return ((void*)s);
		s++;
		n--;
	}
	return (0);
}
