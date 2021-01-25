/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:49:58 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:22:21 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reset_flags(t_data_all *st)
{
	st->field_size = 0;
	st->precision = 0;
	st->size_flags = 0;
	st->is_precision = 0;
	st->size_var = 0;
	st->is_minus = 0;
	st->is_dot = 0;
	st->is_var_print = 1;
	st->tmp_nb = 0;
	st->nbr_neg = 0;
	st->star_right = 0;
	st->star_left = 0;
	st->is_back_zero = 0;
	st->type = 0;
	st->is_zero = 0;
	st->variable = NULL;
	st->tmp = NULL;
	st->tmp2 = NULL;
}

int		ft_sort(va_list ap, t_data_all *st)
{
	if (st->type == 's')
		if (!ft_init_s(ap, st))
			return (0);
	if (st->type == 'd' || st->type == 'i')
		if (!ft_init_d_i(ap, st))
			return (0);
	if (st->type == 'c')
		if (!(st->variable = ft_ctoa(va_arg(ap, int), st)))
			return (0);
	if (st->type == 'p')
		if (!ft_init_p(ap, st))
			return (0);
	if (st->type == 'u')
		if (!ft_init_u(ap, st))
			return (0);
	if (st->type == 'x')
		if (!ft_init_x(ap, st))
			return (0);
	if (st->type == 'X')
		if (!ft_init_x_maj(ap, st))
			return (0);
	if (st->type == '%')
		if (!(st->variable = ft_ctoa('%', st)))
			return (0);
	return (1);
}

int		ft_process(va_list ap, t_data_all *st)
{
	if (!(ft_flags_str(st)))
		return (0);
	ft_detect_flags(ap, st);
	if (!(ft_sort(ap, st)))
		return (0);
	st->size_var += ft_strlen(st->variable);
	if (st->precision < st->size_var && st->type == 's' && st->is_precision)
	{
		if (!(st->variable = ft_substr_free(st->variable, 0, st->precision)))
			return (0);
		st->size_var = st->precision;
	}
	if (st->is_back_zero)
		st->size_var = 1;
	if (!(ft_flags_process(st)))
		return (0);
	st->total_size += st->size_var;
	if (st->is_back_zero && st->is_minus)
		ft_putchar('\0');
	ft_putstr(st->variable);
	if (st->is_back_zero && !st->is_minus)
		ft_putchar('\0');
	ft_strdel(st->flags);
	ft_strdel(st->variable);
	return (1);
}

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	t_data_all	st[1];

	st->i = 0;
	st->total_size = 0;
	va_start(ap, str);
	if (!(st->str = ft_strdup(str)))
		return (-1);
	while (st->str[st->i])
	{
		ft_reset_flags(st);
		if (st->str[st->i] == '%')
			if (!(ft_process(ap, st)))
				return (0);
		if (st->str[st->i] != '\0' && st->str[st->i] != '%')
		{
			ft_putchar(st->str[st->i]);
			st->total_size++;
			st->i++;
		}
	}
	ft_strdel(st->str);
	va_end(ap);
	return (st->total_size);
}
