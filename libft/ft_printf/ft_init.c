/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 14:19:06 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:22:15 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_init_s(va_list ap, t_data_all *st)
{
	st->s = va_arg(ap, char *);
	if (st->s == NULL)
	{
		if (!(st->variable = ft_strdup("(null)")))
			return (0);
	}
	else
	{
		if (!(st->variable = ft_strdup(st->s)))
			return (0);
	}
	return (1);
}

int		ft_init_p(va_list ap, t_data_all *st)
{
	int i;

	i = 0;
	st->tmp = va_arg(ap, void *);
	if (st->precision == 0 && st->tmp == 0 && st->is_precision)
	{
		if (!(st->variable = ft_strdup("0x")))
			return (0);
	}
	else
	{
		while (st->flags[i] && st->flags[i] != '.')
			i++;
		if (st->tmp == NULL && st->flags[i] == '.')
			st->variable = ft_strdup("0x");
		else
			st->variable = ft_strjoin_free_s2("0x",
				ft_itoa_base_ll((unsigned long long)
							st->tmp, "0123456789abcdef"));
		st->tmp = NULL;
	}
	return (1);
}

int		ft_init_u(va_list ap, t_data_all *st)
{
	long u_in;

	u_in = va_arg(ap, int);
	if (st->precision == 0 && u_in == 0 && st->is_precision)
	{
		if (!(st->variable = ft_strdup("")))
			return (0);
	}
	else
	{
		if (u_in < 0)
			u_in = 4294967295 + u_in + 1;
		if (!(st->variable = ft_itoa_ll(u_in)))
			return (0);
	}
	return (1);
}

int		ft_init_x(va_list ap, t_data_all *st)
{
	int nb;

	nb = va_arg(ap, int);
	if (st->precision == 0 && nb == 0 && st->is_precision)
	{
		if (!(st->variable = ft_strdup("")))
			return (0);
	}
	else
	{
		if (!(st->variable = ft_itoa_base_flag_x(nb, "0123456789abcdef")))
			return (0);
	}
	return (1);
}

int		ft_init_x_maj(va_list ap, t_data_all *st)
{
	int nb;

	nb = va_arg(ap, int);
	if (st->precision == 0 && nb == 0 && st->is_precision)
	{
		if (!(st->variable = ft_strdup("")))
			return (0);
	}
	else
	{
		if (!(st->variable = ft_itoa_base_flag_x(nb, "0123456789ABCDEF")))
			return (0);
	}
	return (1);
}
