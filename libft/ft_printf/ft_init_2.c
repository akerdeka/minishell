/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:27:39 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:22:12 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_init_d_i(va_list ap, t_data_all *st)
{
	long nb;

	nb = va_arg(ap, int);
	if (st->is_zero && nb < 0)
		st->field_size--;
	if (nb < 0 && ((st->is_zero && st->field_size > 0) || (st->precision > 0)))
	{
		nb *= -1;
		st->nbr_neg = 1;
	}
	if (st->precision == 0 && nb == 0 && st->is_precision)
	{
		if (!(st->variable = ft_strdup("")))
			return (0);
	}
	else
	{
		if (!(st->variable = ft_itoa_ll(nb)))
			return (0);
	}
	st->type = 'd';
	return (1);
}

char	*ft_ctoa(char c, t_data_all *st)
{
	char *str;

	str = NULL;
	if (c != '\0')
	{
		if (!(str = (char *)malloc(sizeof(char) * (1 + 1))))
			return (NULL);
		str[0] = c;
		str[1] = '\0';
	}
	else
	{
		if (!(str = (char *)malloc(sizeof(char) * (1))))
			return (NULL);
		str[0] = 0;
		st->is_back_zero = 1;
		st->total_size++;
	}
	return (str);
}
