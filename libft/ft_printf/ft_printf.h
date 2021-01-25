/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:41:21 by pbesson           #+#    #+#             */
/*   Updated: 2020/03/11 12:34:39 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft.h"

typedef	struct	s_data_all
{
	int			i;
	int			size_flags;
	int			total_size;
	int			is_precision;
	int			size_var;
	int			nbr_neg;
	int			field_size;
	int			precision;
	int			is_minus;
	int			is_dot;
	int			is_var_print;
	int			tmp_nb;
	int			star_right;
	int			star_left;
	int			is_back_zero;
	int			is_zero;
	char		type;
	char		*variable;
	char		*field_str;
	char		*flags;
	char		*str;
	char		*tmp;
	char		*tmp2;
	char		*s;
}				t_data_all;

int				ft_printf(const char *str, ...);
char			*ft_itoa_base_flag_x(long nbr, char *set);
char			*ft_ctoa(char c, t_data_all *st);
int				ft_process(va_list ap, t_data_all *st);
int				ft_init_s(va_list ap, t_data_all *st);
int				ft_init_p(va_list ap, t_data_all *st);
int				ft_init_u(va_list ap, t_data_all *st);
int				ft_init_x(va_list ap, t_data_all *st);
int				ft_init_x_maj(va_list ap, t_data_all *st);
int				ft_sort(va_list ap, t_data_all *st);
int				ft_flags_str(t_data_all *st);
void			ft_detect_flags(va_list ap, t_data_all *st);
int				ft_flags_process(t_data_all *st);
int				ft_init_d_i(va_list ap, t_data_all *st);

#endif
