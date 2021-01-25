/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:56:17 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:22:09 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		ft_create_field(t_data_all *st, char field_char, int size)
{
	if (st->is_var_print)
		size -= st->size_var;
	if (!(st->field_str = (char *)malloc(sizeof(char) * (1 + size))))
		return (0);
	size--;
	st->field_str[size + 1] = '\0';
	while (size > -1)
	{
		st->field_str[size] = field_char;
		size--;
	}
	if (st->is_minus && field_char == ' ')
		st->variable = ft_strjoin_free(st->variable, st->field_str);
	else
		st->variable = ft_strjoin_free(st->field_str, st->variable);
	st->size_var = ft_strlen(st->variable);
	return (1);
}

int				ft_flags_process(t_data_all *st)
{
	if (st->field_size > 0 || st->precision > 0)
	{
		if (st->field_size > st->size_var && st->is_zero &&
		st->type != 's' && st->type != 'c')
			if (!(ft_create_field(st, '0', st->field_size)))
				return (0);
		if (st->precision > st->size_var && !st->is_zero &&
		st->type != 's' && st->type != 'c' && st->type != '%')
		{
			if (!(ft_create_field(st, '0', st->precision)))
				return (0);
		}
		if (st->nbr_neg)
			if (!(st->variable = ft_strjoin_free_s2("-", st->variable)))
				return (0);
		if (st->nbr_neg)
			st->size_var++;
		if (st->field_size > st->size_var && !st->is_zero)
			if (!(ft_create_field(st, ' ', st->field_size)))
				return (0);
	}
	st->size_var = ft_strlen(st->variable);
	return (1);
}
