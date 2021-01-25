/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:52:59 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:21:05 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char		*ft_convert(char *str, int i, long long nbr)
{
	int min;

	if (str[0] == '-')
		min = 1;
	else
		min = 0;
	str[i + 1] = '\0';
	while (i >= min)
	{
		str[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
	return (str);
}

static void		ft_size(long long *nbr, int *i)
{
	while (*nbr / 10 >= 1 || *nbr / 10 <= -1)
	{
		*nbr /= 10;
		*i += 1;
	}
}

char			*ft_itoa_ll(long long nbr)
{
	char		*str;
	int			i;
	long long	nb_copy;

	i = 1;
	nb_copy = nbr;
	ft_size(&nbr, &i);
	if (nb_copy < 0)
	{
		nb_copy = -nb_copy;
		i++;
		if (!(str = malloc(sizeof(char) * (i + 1))))
			return (0);
		str[0] = '-';
	}
	else
	{
		if (!(str = malloc(sizeof(char) * (i + 1))))
			return (0);
		str[0] = 0;
	}
	i--;
	str = ft_convert(str, i, nb_copy);
	return (str);
}
