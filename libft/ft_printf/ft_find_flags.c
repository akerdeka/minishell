/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 14:03:29 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:22:06 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_precision_dot(t_data_all *st, char *ptr)
{
	ptr = ft_strchr(st->flags, '.') + 1;
	if (ptr)
	{
		st->precision = ft_atoi(ptr);
		st->is_precision = 1;
	}
}

static	void	ft_find_nbr_flags(t_data_all *st)
{
	char	*ptr;
	int		i;
	int		is_field;

	i = -1;
	is_field = 0;
	while (st->flags[++i])
	{
		if (st->flags[i] == '.')
			break ;
		if (st->flags[i] > '0' && st->flags[i] <= '9')
			is_field = 1;
	}
	if (!st->star_left && is_field)
	{
		ptr = ft_strchr_set(st->flags, "123456789");
		if (ptr)
			st->field_size = ft_atoi(ptr);
	}
	if (!st->star_right && st->is_dot)
		ft_precision_dot(st, ptr);
}

static	void	ft_find_stars(va_list ap, t_data_all *st, int i)
{
	i = -1;
	while (st->flags[++i])
	{
		if (st->flags[i] == '*')
		{
			if (i > 0 && st->flags[i - 1] == '.')
			{
				st->star_right = 1;
				st->precision = va_arg(ap, int);
				st->is_precision = 1;
			}
			else
			{
				st->star_left = 1;
				st->field_size = va_arg(ap, int);
				if (st->field_size < 0)
				{
					st->field_size *= -1;
					st->is_minus = 1;
					st->is_zero = 0;
				}
			}
		}
	}
}

int				ft_flags_str(t_data_all *st)
{
	int i;

	st->i++;
	i = st->i;
	while (st->str[i] == '-' || st->str[i] == '0' || st->str[i] == '.' ||
	st->str[i] == '*'
	|| (st->str[i] >= '0' && st->str[i] <= '9'))
		i++;
	st->tmp_nb = (i + 1);
	st->size_flags = i;
	if (!(st->flags = ft_substr(st->str, st->i,
					st->size_flags - (st->i) + 1)))
		return (0);
	st->i = st->tmp_nb;
	st->type = st->str[st->i - 1];
	return (1);
}

void			ft_detect_flags(va_list ap, t_data_all *st)
{
	int i;

	i = 0;
	if (ft_strchr(st->flags, '-'))
		st->is_minus = 1;
	if (ft_strchr(st->flags, '.'))
		st->is_dot = 1;
	while (st->flags[i])
	{
		if ((st->flags[i] > '0' && st->flags[i] <= '9') ||
		(ft_strchr(st->flags, '.') && st->type != '%'))
			break ;
		if (st->flags[i] == '0' && !st->is_minus)
			st->is_zero = 1;
		i++;
	}
	ft_find_stars(ap, st, i);
	if (ft_strlen(st->flags) > 1)
		ft_find_nbr_flags(st);
	if (st->precision < 0)
	{
		st->is_precision = 0;
		st->precision = 0;
	}
}
