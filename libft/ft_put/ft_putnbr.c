/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 08:14:14 by pbesson           #+#    #+#             */
/*   Updated: 2020/02/17 18:22:38 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr(int nb)
{
	long temp;

	temp = nb;
	if (temp < 0)
	{
		ft_putchar('-');
		temp = -temp;
	}
	if (temp > 9)
	{
		ft_putnbr(temp / 10);
		ft_putnbr(temp % 10);
	}
	else
	{
		ft_putchar(temp + '0');
	}
}
