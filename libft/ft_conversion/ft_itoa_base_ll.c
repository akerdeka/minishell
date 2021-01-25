/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:52:59 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:20:53 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char		*ft_convert(char *str, int i, char *set, unsigned long long nbr)
{
	int min;
	int size_set;

	size_set = ft_strlen(set);
	if (str[0] == '-')
		min = 1;
	else
		min = 0;
	str[i + 1] = '\0';
	while (i >= min)
	{
		str[i] = set[nbr % size_set];
		nbr /= size_set;
		i--;
	}
	return (str);
}

static void		ft_size(unsigned long long *nbr, int *i, char *set)
{
	int size_set;

	size_set = ft_strlen(set);
	while (*nbr / size_set >= 1)
	{
		*nbr /= size_set;
		*i += 1;
	}
}

char			*ft_itoa_base_ll(unsigned long long nbr, char *set)
{
	char				*str;
	int					i;
	unsigned long long	nb_copy;

	i = 1;
	nb_copy = nbr;
	ft_size(&nbr, &i, set);
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[0] = 0;
	i--;
	str = ft_convert(str, i, set, nb_copy);
	return (str);
}
