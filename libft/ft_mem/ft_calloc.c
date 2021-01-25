/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:06:22 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:21:41 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	unsigned char	*d;
	size_t			size_alloc;

	size_alloc = size * count;
	if (!(ptr = malloc(size_alloc)))
		return (NULL);
	d = ptr;
	while (size_alloc)
	{
		*d = 0;
		d++;
		size_alloc--;
	}
	return (ptr);
}
