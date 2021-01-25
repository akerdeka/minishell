/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:11:09 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:20:50 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int		ft_base(char *base)
{
	int i;
	int b;

	i = 0;
	b = 1;
	while (base[i + 1])
	{
		if (base[i] == ' ' || base[i] == '-' || base[i] == '+'
				|| (base[i] <= 13 && base[i] >= 9))
			return (0);
		while (base[i + b])
		{
			if (base[i + b] == base[i])
				return (0);
			b++;
		}
		b = 1;
		i++;
	}
	return (i + 1);
}

static int		malo(long nb, int ibase)
{
	int i;

	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb >= ibase)
	{
		nb = nb / ibase;
		i++;
	}
	return (i + 1);
}

static char		*ft_convert_to(long nb, char *base_to, int ibase)
{
	char	*str;
	int		i;
	int		lenght;

	ibase = ft_base(base_to);
	lenght = malo(nb, ibase);
	i = 0;
	if (!(str = malloc((1 + lenght) * sizeof(char))))
		return (0);
	if (nb < 0)
	{
		str[lenght] = '-';
		nb = -nb;
		i++;
	}
	str[lenght--] = '\0';
	while (nb >= ibase)
	{
		str[lenght--] = base_to[nb % ibase];
		nb = nb / ibase;
	}
	if (nb < ibase)
		str[lenght] = base_to[nb % ibase];
	return (str);
}

static int		ft_index(char nbr, char *base_from)
{
	int i;

	i = 0;
	while (base_from[i])
	{
		if (nbr == base_from[i])
			return (i);
		i++;
	}
	return (-1);
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		i;
	long	nb;
	int		ibase;
	int		sign;
	int		index;

	sign = 1;
	i = 0;
	nb = 0;
	ibase = ft_base(base_from);
	while ((nbr[i] <= 13 && nbr[i] >= 9) && nbr[i] == ' ')
		i++;
	while (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i++] == '-')
			sign = -sign;
	}
	while (ft_index(nbr[i], base_from) != -1)
	{
		index = ft_index(nbr[i], base_from);
		nb = nb * ibase + index;
		i++;
	}
	free(nbr);
	return (ft_convert_to(nb * sign, base_to, ibase));
}
